# Proyecto-ED
Entrega final de proyecto de ED para segundo semestre donde hacemos el sistema de examenses pedido desde el documento recibido en moodle

INTRODUCCIÓN
El presente manual de usuario tiene como finalidad explicarel uso del generador de examenes. El sistema cuenta con tres opciones, permite generar examen, modificarlo, además incluye la funcion aplicar examen, puntuando al estudiante en cuestión.
REQUISITOS
•	Compilador c++  compatible con la librería <filesystem>
•	Carpeta de preferencia vacía
•	Persmisos para lectura y escritura de archivos de texto plano(txt)
ESTRUCTURA
Cuenta con un menú principal, con las opciones ya mencionadas.
------------MENU------------
Generar examen.............1
Modificar examen...........2
Aplicar examen.............3
Salir..............................4
Seleccione la opcion que guste realizar.
GENERAR EXAMEN
La opcion 1 cuenta con los siguientes apartados.
Agregar pregunta...........1
Mostrar actual.............2
Siguiente..................3
Anterior...................4
MostrarLista...............5
Guardar y regresar.........6
1.	Agregar pregunta: 
Cada pregunta solicita:
•	pregunta
•	opcion 1
•	opcion 2
•	opcion 3
•	opcion 4
•	respuesta correcta
•	puntaje
Ejemplo:
	Pregunta: ¿Cuánto mide un puntero?
	Opcion1: varia
	Opcion2: 4
	Opcion3: 6
	Opcion4: 8
	Respuesta correcta: 4
	Puntaje: 10
NOTA:
Al ingresar la respuesta correcta tiene que ser de 1 a 4. NO introducir letras
MOSTRAR ACTUAL, SIGUIENTE, ANTERIOR, MOSTRAR LISTA
Permiten al usuario desplazarse entre los reactivos, ademas de imprimr en consola los datos de los reactivos.
