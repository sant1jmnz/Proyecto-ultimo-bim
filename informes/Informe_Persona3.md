# Informe Persona 3: registro de ventas y lectura de datos

Trabajo Integrador 4to bimestre, Sistema de Punto de Venta y Stock.

## Parte 3: Registro de venta y validaciones

### 1. ¿Por qué `exec()` es la elección más adecuada para registrar ventas, en lugar de `show()`?

La venta es una operación que tiene que terminar (confirmar o cancelar) antes de seguir. `exec()` detiene el código hasta que se cierra la ventana y devuelve `QDialog::Accepted` o `Rejected`. Así, el código que resta el stock está justo después y solo se ejecuta si el usuario confirmó. Con `show()` el código seguiría de largo y habría que usar señales para enterarse del resultado.

### 2. ¿Qué implica que un `QDialog` sea modal y cómo restringe la interacción?

Mientras el diálogo modal está abierto, el usuario no puede interactuar con las otras ventanas de la aplicación. La ventana principal no responde a los clics hasta que se cierre la venta. Eso evita que, por ejemplo, alguien elimine o edite el producto que se está vendiendo en ese momento.

### 3. ¿Qué validaciones son imprescindibles antes de restar la cantidad del stock?

Hay que comprobar que la cantidad sea un número entero, que sea mayor que cero y que no supere el stock disponible. En `Venta::on_btnConfirmar_clicked()` se lee la cantidad y el stock con `toInt()` y se revisan dos condiciones: si la cantidad es menor o igual a cero y si es mayor que el stock. Solo si ambas pasan se llama a `accept()`. Con esas dos comprobaciones el stock nunca queda negativo.

### 4. ¿Cómo implementaría una alerta visual si se intenta vender más que el stock?

Con un `QMessageBox::warning(this, "Alerta de Stock", "No hay suficiente stock para vender esa cantidad.")` seguido de `return`. Como no se llega a llamar a `accept()`, el diálogo queda abierto y el usuario puede corregir la cantidad sin perder lo demás.

### 5. ¿Por qué cargar las imágenes con el sistema de recursos (`.qrc`) y no con rutas absolutas?

Los archivos `.qrc` se compilan dentro del ejecutable, así que las imágenes viajan con el programa. Una ruta absoluta como `C:\Users\...` solo existe en una computadora y en otra la imagen no aparece. Con el recurso la ruta es `":/imagenes/imagenes/" + nombreProducto + ".jpg"` y funciona en cualquier PC. La imagen se escala con `scaled(..., Qt::KeepAspectRatio)` para que entre en el `QLabel` sin deformarse. Si no existe la imagen del producto, se carga `default.png`.

### 6. ¿Cómo se asegura que la cantidad acepte solo enteros positivos (por ejemplo con `QIntValidator`)?

Un `QIntValidator` con un rango mínimo de 1, aplicado con `setValidator` a un `QLineEdit`, impide escribir letras, signos negativos y decimales. En nuestra ventana usamos un `QSpinBox` con `setRange(1, 999999)`, que solo admite enteros dentro de ese rango, y además se revisa el valor al confirmar.

### 7. ¿Qué acciones adicionales debería disparar el sistema si el stock llega a cero tras una venta?

En el proyecto, después de restar el stock, si el resultado es 0 se muestra un `QMessageBox::information` que avisa que el producto se quedó sin stock. Como la validación no deja vender más de lo que hay, ya no se puede registrar otra venta de ese producto. Como mejoras posibles quedarían resaltar la fila o avisar que hay que reponer, pero eso no está hecho.

## Parte 4: Persistencia (lectura)

### 5. ¿Qué estrategias usaría para evitar caídas si el archivo binario está dañado?

En `cargarDatos()` se revisa que `open()` tenga éxito. Dentro del ciclo que lee cada producto se consulta `entrada.status() != QDataStream::Ok` justo después de leer los campos: si el estado no es correcto se hace `break` y no se agrega esa fila con datos basura. Probamos el programa con un archivo `datos.bin` lleno de texto cualquiera y no se cerró. Lo que se pierde en ese caso es el inventario guardado, pero el programa arranca.

### 6. ¿Qué impacto tiene en la experiencia de usuario mantener la persistencia total, incluyendo categorías, origen e IVA?

El usuario retoma el trabajo exactamente donde lo dejó y no tiene que volver a cargar nada a mano. Si solo se guardaran el nombre, el precio y el stock, al reabrir el programa el IVA y el origen volverían a valores por defecto y los datos del inventario estarían mal sin que nadie lo note. Que todo vuelva igual da confianza en el sistema.

### 7. Por el principio de responsabilidad única, ¿por qué aislar la lectura y escritura de archivos en funciones dedicadas?

`guardarDatos()` y `cargarDatos()` solo se ocupan del archivo, y los slots de la interfaz solo leen y muestran datos. Así, si cambia el formato o la ruta del archivo, se modifican esas dos funciones y no el resto. Además se reutilizan: `guardarDatos()` se llama desde `closeEvent`, y `cargarDatos()` desde el constructor, y el código de cada parte es más corto y fácil de leer.
