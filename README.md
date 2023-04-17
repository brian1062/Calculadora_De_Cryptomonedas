

# Calculadora de Criptomonedas

Este proyecto es una calculadora de criptomonedas que permite convertir el valor de una criptomoneda a otra utilizando una API REST. El proyecto está escrito en lenguaje C y Python.
[Presentacion](https://docs.google.com/presentation/d/1r7xv7Jz9xSBwO4W7NpnOmjwHPNZXW06ScLB5h36pCPw/edit?usp=share_link).

## Compilación

Para compilar el proyecto, se debe utilizar el comando `make` en la línea de comandos.
``` 
make
``` 
Esto generará un archivo ejecutable llamado `main`.

## Ejecución

Para ejecutar el programa, primero es necesario ejecutar el archivo `crypto.py` utilizando el comando.
``` 
python3 crypto.py
``` 
Esto permitirá que el programa se comunique con la API REST y acceda a los datos necesarios.

Una vez que `crypto.py` está en ejecución, podemos ejecutar en una nueva terminal el programa principal utilizando el comando.
``` 
./main
``` 
Este programa solicita al usuario que ingrese la abreviación del nombre de una criptomoneda "ETH o BTC" la que desea convertirla. A continuación, el programa se comunica con la API REST para obtener las tasas de conversión y realiza el cálculo necesario para mostrar el resultado al usuario.
## UML
**![](https://lh4.googleusercontent.com/1D4AhRKN4CP9tq8p8BeXainWJHmkiwWXpUcDbzDtzyCXOK7UL1WasMhM77cv_08BFZzz-Ai3d7d8zNja_qU2t9kKXBIIytkmgDG5kXp3CYTTms4N3V_CwD4KuH9nVC1v74_igjXoj0Ao4roSE_ZeZrn_Ag=nw)**
##
## Características

La calculadora de criptomonedas tiene las siguientes características:

-   Conversión de valor de una criptomoneda a otra utilizando una API REST.
-   Admite una amplia variedad de criptomonedas.
-   Interfaz de línea de comandos simple y fácil de usar.

## Contribuciones

Este proyecto es de código abierto y las contribuciones son bienvenidas. Si deseas contribuir, simplemente haz un fork del repositorio y crea una nueva rama para tus cambios. Luego, crea una solicitud de extracción para que los cambios puedan ser revisados y fusionados con la rama principal.
