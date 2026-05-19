## Concurrencia

¡IMPORTANTE! Si en los enunciados no piden que evitemos la inanición, **NO LO HACEMOS SI NO ES MUY SENCILLO** (como en todos estos ejs lol), esto nos lo dijo en teoría el día q los hicimos. 

### Para el ej 1:
- El #define de CAR_AMOUNT decide la cantidad de threads, si quieres que acabe antes, bajale un poco
- No hay cambios al enunciado en `car()`, y el `main()` no lo pedían, lo único que tiene añadido es temporizadores para poder comprobar sin la linealidad del for(...){pthread_init()}
- Si Quieres probar que tu código funciona, reemplaza las definiciones de `enter_bridge()` y `exit_bridge()` y ejecuta.  
Yo recomendaría poner un `print + flush` al "liberar" el puente como en los que hice para ver que realmente no se mezclan

### Para el ej 2:
- Las comprobaciones son más ásperas que en el ej1, debes revisar manualmente el log tras ejecutar y revisar que nunca se pase de la cantidad y no entre en bloqueos _inesperados_
- Recuerda que la probabilidad no es ciencia cierta, si entra en un bucle de espera infinito por ser el grupo más grande que el propio museo, mata al proceso y vuelvelo a lanzar.
- El log tiene los siguientes tipos de entradas: 
    - `<!>` -> el grupo _empieza a comprobar si tiene hueco_ para entrar
    - `-E-` -> el grupo _empieza a entrar_ por tener hueco (NO ES CUANDO EMPIEZAN LA VISITA)
    - `[L]` -> el grupo abandonó por completo el museo