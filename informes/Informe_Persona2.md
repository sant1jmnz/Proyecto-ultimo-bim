# Informe Persona 2: formulario de creación y edición

Trabajo Integrador 4to bimestre, Sistema de Punto de Venta y Stock.

## Parte 2: Formulario de creación y edición

### 1. ¿Cuál es el propósito visual y lógico de encapsular controles con un `QGroupBox`?

Visualmente, el `QGroupBox` dibuja un marco con título que separa sectores del formulario. En el nuestro hay dos: "Datos del producto", con lo que se escribe (ID, nombre, precio y stock), y "Clasificación", con lo que se elige (categoría, IVA y origen). Lógicamente, agrupa controles relacionados: los dos `QRadioButton` de origen están dentro del mismo grupo y por eso son excluyentes entre sí, si se marca uno el otro se desmarca.

### 2. ¿Por qué se exige memoria dinámica (`new`) al instanciar el formulario con `show()`?

Porque `show()` no espera: muestra la ventana y la función que la creó sigue y termina enseguida. Con `new`, el objeto vive en el heap hasta que se libere y la ventana queda abierta, así el usuario puede seguir usando la tabla de fondo mientras completa el formulario.

### 3. ¿Qué sucedería con la ventana si se usara memoria estática (Stack) con `show()` al terminar la función?

La variable local se destruiría al salir de la función, y con ella la ventana. El formulario aparecería un instante y desaparecería, sin que el usuario pueda escribir nada. Con `exec()` no pasa porque esa llamada espera a que se cierre la ventana, por eso la ventana de venta sí puede estar en el stack.

### 4. ¿Por qué es necesario convertir los textos del modelo a tipos numéricos como `double` o `int`?

El modelo guarda todo como texto, y con texto no se puede operar: para comparar precios, restar stock o validar una venta hacen falta números reales. Por eso se usan `.toDouble()` y `.toInt()` al sacar los datos de la tabla, y `QString::number()` para volver a ponerlos como texto cuando se escriben de nuevo en la tabla o en los controles.

### 5. ¿De qué manera `cargarDatosEdicion` ayuda al encapsulamiento y al bajo acoplamiento?

Los controles del formulario (`leNombre`, `lePrecio`, etc.) son privados. La ventana principal no los toca directamente, solo llama a la función pública `cargarDatosEdicion(...)` y le pasa los valores. Si mañana cambiáramos un `QLineEdit` por otro control dentro del formulario, la ventana principal seguiría funcionando mientras la función mantenga los mismos parámetros.

### 6. ¿Qué diferencia hay entre el operador flecha (`->`) y el punto (`.`)?

El punto se usa con un objeto directo, como la `Venta ventanaVenta` del stack: `ventanaVenta.exec()`. La flecha se usa con un puntero, como el formulario creado con `new`: `ventana->cargarDatosEdicion(...)`. La flecha equivale a desreferenciar el puntero y luego usar el punto, o sea `(*ventana).cargarDatosEdicion(...)`.

### 7. ¿Cómo se asegura que `QComboBox` o `QCheckBox` reflejen el estado exacto extraído de un texto de la tabla?

Se convierte el texto al tipo que necesita cada control. Para el combo se usa `cbCategoria->setCurrentText(categoria)`, que selecciona el ítem con ese texto. Para el IVA se compara el texto con "Sí", se obtiene un `bool` y se usa `chkIva->setChecked(aplicaIva)`. Para el origen se compara con "Importado" y se hace `rbImportado->setChecked(importado)` y `rbNacional->setChecked(!importado)`. El texto tiene que coincidir exactamente con el que se escribió en la tabla.

### 8. ¿Qué riesgo hay en no validar campos vacíos antes de `toDouble()` o `toInt()`?

Esas funciones no dan error: si el campo está vacío o tiene letras, devuelven 0 sin avisar. Un producto podría guardarse con precio 0 o stock 0 y nadie se daría cuenta. Para evitarlo, en `on_btnGuardar_clicked()` se revisa primero `isEmpty()` en cada campo y, si falta alguno, se muestra un `QMessageBox::warning` y se hace `return`. Además, el precio usa un `QDoubleValidator` y el stock un `QIntValidator`, que impiden escribir letras. Debajo del precio hay un aviso de que los decimales van con punto y no con coma.

### 9. ¿Cómo manejaría la memoria al cerrar el formulario (`deleteLater()`) si el usuario cancela o cierra la ventana?

Al crear el formulario se conecta `connect(ventana, &QDialog::finished, ventana, &QObject::deleteLater)`. Cuando el usuario guarda, cancela o cierra con la X, el diálogo emite `finished` y el objeto se libera. Se usa `deleteLater()` y no `delete` porque la ventana podría estar todavía ejecutando uno de sus slots, y así Qt la borra cuando termina. Sin esta conexión, el formulario quedaría ocupando memoria hasta cerrar la ventana principal, ya que la ventana principal es su padre.
