#include "unity.h"
#include "clock.h"

#define TICKS_PER_SECOND 5
/*
1) Configurar la libreria, consultar la hora y tiene que ser invalida
2) Configurar la libreria, ajustar la hora(con valores correctos), consultar la hora y tiene que ser valida.
3) Configurar la libreria, ajustar la hora(con valores incorrectos), tiene que devolver que es un error.
4) Simujlar el paso de n ciclos de reloj, consultar la hora y verificar que avanzo un segundo.
5) Simujlar el paso de 10*n ciclos de reloj, consultar la hora y verificar que avanzo diez segundos.
.... y con 60*n, etc
6) Configurar la hora de la alarma (con valores correctos) y revisar si la guarda.
7) Configurar la hora de la alarma (con valores incorrectos) y revisar si la rechaza.
8) Configurar la hora de la alarma (con valores correctos) y revisar si queda activa.
9) Si la alarma esta activa y la desactivo , queda desactivada, pero no cambia la hora.
10) Si la alamra esta desctivada y la activo, queda activa, pero no cambia la hora.
11) Si la alarma activa, y la hora del reloj councide con la hora de la alarma, entoces suena.
12) Si la alarma se activo y la pospongo n minutos, vuelve a sonar n minutos.
12) Si la alarma se activo y la cancelo vuelve a sonar 24 horas despues.
*/

clock_t reloj;

void setUp(void){
    static const uint8_t INICIAL[] = {1, 2, 3, 4};
    reloj = ClockCreate(TICKS_PER_SECOND);
    ClockSetupTime(reloj, INICIAL, sizeof(INICIAL));
}
//1) Configurar la libreria, consultar la hora y tiene que ser invalida
void test_start_up(void){
    static const uint8_t ESPERADO[] = {0, 0, 0, 0, 0, 0};
    uint8_t hora[6];
    clock_t reloj = ClockCreate(TICKS_PER_SECOND);
    TEST_ASSERT_FALSE(ClockGetTime(reloj, hora, sizeof(hora)));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, sizeof(ESPERADO));

}


// 2) Configurar la libreria, ajustar la hora(con valores correctos), consultar la hora y tiene que ser valida.

void test_set_up_current_time(void){
    static const uint8_t ESPERADO[] = {1, 2, 3, 4, 0, 0};
    uint8_t hora[6];
    TEST_ASSERT_TRUE(ClockGetTime(reloj, hora, sizeof(hora)));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, sizeof(ESPERADO));
}

//4) Simujlar el paso de n ciclos de reloj, consultar la hora y verificar que avanzo un segundo.

void test_one_second_elapsed(void){

    static const uint8_t ESPERADO[] = {1, 2, 3, 4, 0, 1};
    uint8_t hora[6];

    for(int index = 0; index < TICKS_PER_SECOND; index++){
        ClockNewTick(reloj);
    }
    ClockGetTime(reloj, hora, sizeof(hora));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, sizeof(ESPERADO));
}