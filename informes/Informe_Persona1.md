# Informe Persona 1: panel principal y guardado

Trabajo Integrador 4to bimestre, Sistema de Punto de Venta y Stock.

## Parte 1: Panel principal

### 1. ¿Por qué es fundamental iniciar los botones de acción en estado desactivado?

Porque al abrir la aplicación todavía no hay ningún producto seleccionado. Si Editar o Eliminar estuvieran activos, el usuario podría tocarlos sin tener una fila elegida y el programa trabajaría con un índice que no existe (la fila -1). Eso termina en un error o en un cierre inesperado. Con `setEnabled(false)` en el constructor, además, la interfaz le muestra al usuario que primero tiene que elegir un producto.

### 2. ¿Cómo se asegura que la señal `clicked` corresponda a un índice válido antes de habilitar los botones?

El slot `on_tableView_clicked(const QModelIndex &index)` recibe el índice como parámetro y pregunta `if (index.isValid())` antes de llamar a `setEnabled(true)`. Si el usuario hace clic en una zona vacía de la grilla, el índice llega inválido y los botones siguen apagados. Además, cada acción que usa la selección revisa que `currentIndex().row()` no sea -1 y, si lo es, muestra un `QMessageBox::warning`.

### 3. ¿Qué impacto tiene en la usabilidad un menú contextual (`QMenu`) en lugar de depender solo de botones estáticos?

El menú aparece justo donde está el cursor, sobre el producto que se quiere usar, así que el usuario no tiene que llevar el mouse hasta los botones de abajo. En nuestro caso el clic derecho además selecciona la fila bajo el cursor y activa las acciones. Los botones siguen estando, así que el menú es un acceso rápido extra y no los reemplaza.

### 4. ¿De qué manera el patrón Modelo-Vista facilita la actualización en tiempo real del inventario visual?

El `QTableView` no guarda datos, solo muestra lo que tiene el modelo (`QStandardItemModel`). Cuando el modelo cambia, por ejemplo con `appendRow`, `setText` o `removeRow`, avisa internamente a la vista y esta se redibuja sola. No hace falta recorrer la tabla a mano. Lo mismo pasa con el filtro: el `QSortFilterProxyModel` va entre el modelo y la vista, y al cambiar el texto de búsqueda la grilla se actualiza al instante.

### 5. ¿Cómo implementaría un mecanismo para volver a desactivar los botones si el modelo queda vacío tras una búsqueda?

En el slot `on_lineEdit_textChanged`, después de aplicar `setFilterFixedString`, se pregunta `if (filtroInventario->rowCount() == 0)` y en ese caso se llama a `setEnabled(false)` en los botones de acción. Así, si la búsqueda no encuentra nada, no queda ningún botón activo sobre una selección que ya no se ve. Esto es lo que hicimos en el proyecto.

## Parte 4: Persistencia (escritura y arranque)

### 1. ¿Cuál es el beneficio de sobrescribir `closeEvent` en lugar de depender de un botón "Guardar"?

El guardado pasa a ser automático. Con un botón, el usuario tiene que acordarse de apretarlo y, si se olvida, pierde los cambios. `closeEvent` es el punto por el que pasa cualquier cierre de la ventana (la X o Alt+F4), así que el guardado se hace siempre. En él llamamos a `guardarDatos()` y terminamos con `event->accept()` para que la ventana se cierre.

### 2. ¿Qué ventajas ofrece la serialización binaria con `QDataStream` sobre un archivo de texto plano como CSV o TXT?

`QDataStream` guarda cada dato con su tipo exacto (`int`, `double`, `bool`, `QString`), sin convertirlo a texto y volver a convertirlo. En un CSV un nombre con una coma rompería las columnas, y acá no pasa porque no hay separadores. El archivo también es más compacto y rápido de leer. Hay que aclarar que no es cifrado: el binario evita que alguien lo edite por accidente con el bloc de notas, pero no protege los datos de una persona que quiera abrirlo.

### 3. ¿Qué pasos son necesarios para serializar un estado booleano, como un `QCheckBox`, junto con cadenas de texto?

Primero se obtiene el valor como `bool`, por ejemplo comparando el texto de la columna IVA con "Sí". Después se escribe en el mismo flujo con `<<`, en un orden fijo: id, nombre, categoría, precio, stock, aplicaIva e importado. `QDataStream` acepta `bool` directamente, no hace falta convertirlo. Al leer se usa `>>` con los mismos tipos y en el mismo orden, y con esos valores se reconstruye el texto de la tabla ("Sí" o "No", "Importado" o "Nacional").

### 4. ¿Por qué es crítico reconstruir el inventario en el constructor y qué validación debe existir si `datos.bin` no se encuentra?

Porque la tabla tiene que estar completa antes de que el usuario la vea. Si se cargara después, vería la tabla vacía o podría operar sobre datos incompletos. En la primera ejecución el archivo no existe, y `archivo.open(QIODevice::ReadOnly)` devuelve `false`. Con un `if` sobre ese resultado, la carga se saltea y la tabla queda vacía sin ningún error.
