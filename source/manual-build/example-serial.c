/*
 * hello-world to demonstrate manual compiling/linking an ADIOS2 example
 */

#include <stdio.h>  //printf
#include <stdlib.h> //calloc, free

#include <adios2_c.h>

void writer(adios2_adios *adios, const char *greeting)
{
    adios2_io *io = adios2_declare_io(adios, "hello-world-writer");
    adios2_variable *var_greeting = adios2_define_variable(
        io, "Greeting", adios2_type_string, 0, NULL, NULL, NULL, adios2_constant_dims_true);

    adios2_engine *engine = adios2_open(io, "example-serial-c.bp", adios2_mode_write);
    adios2_put(engine, var_greeting, greeting, adios2_mode_deferred);
    adios2_close(engine);
}

void reader(adios2_adios *adios, char *greeting)
{
    adios2_io *io = adios2_declare_io(adios, "hello-world-reader");
    adios2_engine *engine = adios2_open(io, "example-serial-c.bp", adios2_mode_read);
    adios2_variable *var_greeting = adios2_inquire_variable(io, "Greeting");
    adios2_get(engine, var_greeting, greeting, adios2_mode_deferred);
    adios2_close(engine);
}

int main(int argc, char *argv[])
{
    adios2_adios *adios = adios2_init(adios2_debug_mode_on);

    const char greeting[] = "Hello World from ADIOS2 C/Serial example";
    writer(adios, greeting);

    char *message = (char *)calloc(1,sizeof(greeting)+1);
    reader(adios, message);
    printf("%s\n", message);

    free(message);

    return 0;
}
