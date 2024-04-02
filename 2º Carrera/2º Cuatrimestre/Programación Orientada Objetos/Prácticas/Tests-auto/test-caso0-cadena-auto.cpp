/* $Id: test-caso0-cadena-auto.cpp $
 *
 * Pruebas unitarias automáticas para la clase Cadena (P0, P1)
 *
 * ©2014 Antonio G.ª Dguez.
 * ©2015-23 el resto de profesores de POO
 */
#include "test-auto.hpp"
#include <sys/resource.h>   // prlimit

using namespace std;

namespace {
   bool bPrimera = true;
}

// Para comprobar el lanzamiento de excepción
// y mostrar una cadena (TXT) más específica.
#define fct_xchk_ex(EXCEPTION, CODE, TXT)   \
   {                                        \
      bool pass_chk_ex = false;             \
      try {                                 \
          CODE;                             \
          pass_chk_ex = false;              \
      } catch ( EXCEPTION ) {               \
          pass_chk_ex = true;               \
      } catch ( ... ) {                     \
          pass_chk_ex = false;              \
      }                                     \
      fct_xchk(                             \
    pass_chk_ex,                            \
        TXT                                 \
        "se esperaba la excepción %s.",     \
        #EXCEPTION                          \
      );                                    \
   }

FCTMF_SUITE_BGN(test_cadena) {

  if (bPrimera) {
    bPrimera = false;
    cerr << "\n---------- PRÁCTICA "
#ifdef P0
      "0"
#else
      "1"
#endif
      ": CADENA ----------\n" << endl;
  }
  FCT_TEST_BGN(Cadena - Ctor: repetir caracter ciertas veces) {
    const Cadena a(5, '*');
    const Cadena b(0, '*');
    fct_xchk(strcmp(a.operator const char*(), "*****") == 0, 
              "Constructor de cadena con carácter repetido: "
              "la cadena creada no tiene el contenido esperado.");
    fct_xchk(a.length() == 5, "Constructor de cadena con carácter repetido: "
              "la cadena creada debería tener %d caracteres, "
              "pero length() indica que son %d.", 
              5, a.length());
    fct_xchk(strcmp(b.operator const char*(), "") == 0, "Constructor de cadena "
              "con carácter repetido para el caso de 0 repeticiones: "
              "la cadena obtenida debería ser igual a la cadena vacía (\"\").");
    fct_xchk(b.length() == 0, "Constructor de cadena con carácter repetido "
              "para el caso de 0 repeticiones: "
              "la cadena creada debería tener %d caracteres, "
              "pero length() indica que son %d.", 
              0, b.length());
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Cadena - Ctor: entero - repite espacios) {
    const Cadena a(10);
    const Cadena b(size_t(0));
    fct_xchk(strcmp(a.operator const char*(), "          ") == 0, 
              "Constructor de cadena con un parámetro entero mayor que 0: "
              "la cadena creada no tiene el contenido esperado.");
    fct_xchk(a.length() == 10, 
              "Constructor de cadena con un parámetro entero mayor que 0: "
              "la cadena creada debería tener %d caracteres, "
              "pero length() indica que son %d.", 
              10, a.length());
    fct_xchk(strcmp(b.operator const char*(), "") == 0, 
              "Constructor de cadena con un parámetro entero igual a 0: "
              "la cadena obtenida debería ser igual a la cadena vacía (\"\").");
    fct_xchk(b.length() == 0, 
              "Constructor de cadena con un parámetro entero igual a 0: "
              "la cadena creada debería tener %d caracteres, "
              "pero length() indica que son %d.", 
              0, b.length());
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Cadena - Ctor: sin parametros - vacia) {
    const Cadena a, b;
    fct_xchk(strcmp(a.operator const char*(), "") == 0, 
              "Constructor de cadena sin parámetros: "
              "la cadena creada debería ser igual a la cadena vacía (\"\").");
    fct_xchk(a.length() == 0, "Constructor de cadena sin parámetros: "
              "la cadena creada debería tener %d caracteres, "
              "pero length() indica que son %d.", 
              0, a.length());
    fct_xchk(a.operator const char *() == b.operator const char*(), 
              "Constructor de cadena sin parámetros: el operador const char*() "
              "devuelve diferentes direcciones para cadenas vacías.");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Cadena - Ctor: por copia de otra cadena) {
    const size_t n = 3;
    const Cadena a(n);
    const Cadena b(a);
    fct_xchk(strcmp(b.operator const char*(), "   ") == 0, 
              "Constructor por copia de cadena: "
              "la copia debería contener una cadena igual a \"   \".");
    fct_xchk(b.length() == n, 
              "Constructor por copia de cadena: la copia debería tener %d "
              "caracteres, pero length() indica que son %d.", n, b.length());
    fct_xchk(a.operator const char *() != b.operator const char*(), 
              "Constructor por copia de cadena: el operador const char*() "
              "devuelve la misma dirección de cadena de bajo nivel para "
              "la cadena original y la copia.");
    const Cadena c;
    const Cadena d(c);
    fct_xchk(strcmp(d.operator const char*(), "") == 0, 
              "Constructor por copia de cadena vacía: "
              "la copia debería ser igual a la cadena vacía (\"\").");
    fct_xchk(d.length() == 0, "Constructor por copia de cadena vacía: "
              "la longitud de la copia debería ser igual a %d.", 0);
    fct_xchk(c.operator const char *() == d.operator const char*(), 
              "Constructor por copia de cadena vacía: el operador const char*() "
              "devuelve diferentes direcciones de cadena de bajo nivel para "
              "la cadena original y la copia.");
  }
  FCT_TEST_END();
  // Solo en P1, no se pide en P0
#ifndef P0
  FCT_TEST_BGN(Cadena - Ctor: de movimiento) {
    Cadena a(3);
    const char* c = a.operator const char*();
    const Cadena b(std::move(a));
    fct_xchk(b.operator const char*() == c, 
              "Constructor de movimiento de cadena: "
              "el operador const char*() de la cadena destino debería ser "
              "igual al de la cadena original.");
    fct_xchk(strcmp(b.operator const char*(), "   ") == 0, 
              "Constructor de movimiento de cadena: "
              "la cadena destino debería contener una cadena igual a \"   \".");
    fct_xchk(b.length() == 3, "Constructor de movimiento de cadena: "
              "la longitud de la cadena destino debería ser igual a %d.", 3);
    fct_xchk(a.operator const char *() != c,
              "Constructor de movimiento de cadena: el operador "
              "const char*() de la cadena origen debería devolver una "
              "dirección diferente de la previa al movimiento.");
    fct_xchk(a.length() == strlen(a.operator const char *()), 
              "Constructor de movimiento de cadena: "
              "la cadena origen debería quedar con una longitud igual al "
              "número de caracteres que contiene.");
    Cadena d;
    c = d.operator const char*();
    const Cadena e(std::move(d));
    fct_xchk(e.operator const char*() == c, 
              "Constructor de movimiento de cadena origen vacía: "
              "el operador const char*() de la cadena destino debería ser "
              "igual al de la cadena original.");
    fct_xchk(strcmp(e.operator const char*(), "") == 0, 
              "Constructor de movimiento de cadena origen vacía: "
              "la cadena destino debería contener una cadena igual a \"\".");
    fct_xchk(e.length() == 0, "Constructor de movimiento de cadena origen vacía: "
              "la longitud de la cadena destino debería ser igual a %d.", 0);
    fct_xchk(d.length() == strlen(a.operator const char *()), 
              "Constructor de movimiento de cadena origen vacía: "
              "la cadena origen debería quedar con una longitud igual al "
              "número de caracteres que contiene.");
    fct_xchk(d.operator const char *() == e.operator const char*(), 
              "Constructor de movimiento de cadena origen vacía: "
              "el operador const char*() devuelve diferentes direcciones de "
              "cadena de bajo nivel para la cadenas original y destino.");
  }
  FCT_TEST_END();
#endif
  FCT_TEST_BGN(Cadena - Ctor: desde cadena de bajo nivel) {
    const Cadena a("hola");
    fct_xchk(strcmp(a.operator const char*(), "hola") == 0, 
              "Constructor desde cadena de bajo nivel: "
              "la cadena destino debería contener una cadena igual a \"hola\".");
      fct_xchk(a.length() == 4, "Constructor desde cadena de bajo nivel: "
              "la longitud de la cadena original debería ser igual a %d.", 4);
    const char* b = "";
    const Cadena c(b);
    fct_xchk(strcmp(c.operator const char*(), "") == 0, 
              "Constructor desde cadena de bajo nivel vacía: "
              "la cadena destino debería contener una cadena igual a \"\".");
    fct_xchk(c.length() == 0, "Constructor desde cadena de bajo nivel vacía: "
              "la longitud de la cadena destino debería ser igual a %d.", 0);
    fct_xchk(c.operator const char*() != b, 
              "Constructor desde cadena de bajo nivel vacía: "
              "el operador const char*() de la nueva cadena no debe apuntar "
              "a la misma cadena de bajo nivel parámetro del constructor.");
  }
  FCT_TEST_END();
  FCT_TEST_BGN(Cadena - Asignar una cadena a otra: copia) {
    Cadena a("adios");
    const char* d = a.operator const char*();
    a = static_cast<Cadena&>(a);
    fct_xchk(strcmp(a.operator const char*(), "adios") == 0,
              "Autoasignación de copia: "
              "la cadena no debería cambiar de contenido.");
    fct_xchk(a.length() == 5, 
              "Autoasignación de copia: "
              "la cadena no debería cambiar de longitud.");
    fct_xchk(a.operator const char*() == d, 
              "Autoasignación de copia: "
              "la dirección del operador const char*() de la "
              "cadena no debería cambiar.");
    const Cadena b;
    a = b;
    fct_xchk(strcmp(a.operator const char*(), "") == 0, 
              "Asignación de cadena vacía: "
              "la cadena destino debería contener una cadena igual a la que "
              "aparece a la derecha del igual, que está vacía (\"\").");
    fct_xchk(a.length() == 0, "Asignación de cadena vacía: "
              "la longitud de la cadena destino debería ser igual a %d.", 0);
    fct_xchk(a.operator const char*() == b.operator const char*(), 
              "Asignación de cadena vacía: el operador const char*() "
              "devuelve diferentes direcciones de cadena de bajo nivel "
              "para las cadenas a la derecha e izquierda del igual.");
    const Cadena c(3);
    a = c;
    fct_xchk(strcmp(a.operator const char*(), "   ") == 0, 
              "Asignación de cadena no vacía: la cadena destino no contiene "
              "una cadena igual a la que aparece a la derecha del igual.");
    fct_xchk(a.length() == 3, "Asignación entre cadenas: "
              "la longitud de la cadena destino debería ser igual a %d.", 3);
    fct_xchk(a.operator const char *() != c.operator const char*(), 
              "Asignación de cadena no vacía: el operador const char*() "
              "devuelve la misma dirección de cadena de bajo nivel para "
              "las cadenas a la derecha e izquierda del igual.");
  }
  FCT_TEST_END();

// Valgrind interfiere con prlimit. Las siguiente pruebas de memoria emplean
// prlimit para reducir la memoria disponible para el proceso y forzar el
// lanzamiento de la excepción std::bad_alloc en las funciones miembro
// modificadoras que pueden lanzar bad_alloc.
  
// #ifndef VALGRIND
//   FCT_TEST_BGN(Cadena - Asignar una copia: memoria no disponible) {
//     rlimit ant, nuevo{1536 * 1024, 1536 * 1024}; // máx. memoria disponible 1,5 MiB
//     if (prlimit(0, RLIMIT_DATA, &nuevo, &ant) == 0) {

//       Cadena c(3, '+');
      
//       const char* d = c.operator const char*();
      
//       vector<Cadena> vcad;
  
//       try {
//         while(true)
//         vcad.push_back(Cadena(1023, '@')); //aqui peta -> bucle infinito
//       } catch (bad_alloc&) {}

//       try {
//         c = vcad[0];

//       } catch (bad_alloc&) {
//         fct_xchk(strcmp(c.operator const char*(), "+++") == 0, 
//                   "Asignación de copia: memoria insuficiente ('std::bad_alloc'). "
//                   "La cadena destino no debería cambiar de contenido.");
//         fct_xchk(c.length() == 3,
//                   "Asignación de copia: memoria insuficiente ('std::bad_alloc'). "
//                   "La cadena destino no debería cambiar de longitud.");
//         fct_xchk(c.operator const char *() == d,
//                   "Asignación de copia: memoria insuficiente ('std::bad_alloc'). "
//                   "la dirección del operador const char*() de la "
//                   "cadena no debería cambiar.");
//       }
//       prlimit(0, RLIMIT_DATA, &ant, nullptr);
//     }    
//     else
//       cerr << "\n   Test no realizado: error de limitación de memoria.\n";
//   }
//   FCT_TEST_END();
// #endif

  // Solo en P1, no se pide en P0
#ifndef P0
  FCT_TEST_BGN(Cadena - Asignar una cadena a otra: movimiento) {
    Cadena a("hola");
    const char* c = a.operator const char*();
    a = static_cast<Cadena&&>(a);
    fct_xchk(strcmp(a.operator const char*(), "hola") == 0,
              "Autoasignación de movimiento: "
              "la cadena no debería cambiar de contenido.");
    fct_xchk(a.length() == 4, 
              "Autoasignación de movimiento: "
              "la cadena no debería cambiar de longitud.");
    fct_xchk(a.operator const char*() == c, 
              "Autoasignación de movimiento: "
              "la dirección del operador const char*() de la "
              "cadena no debería cambiar.");
    Cadena b("adios");
    c = b.operator const char*();
    a = std::move(b);
    fct_xchk(a.operator const char*() == c, 
              "Asignación por movimiento entre cadenas: "
              "el operador const char*() de la cadena a la izquierda del igual "
              "debería devolver la dirección de bajo nivel de la cadena "
              "a la derecha del igual, tras la asignación por movimiento.");
    fct_xchk(strcmp(a.operator const char*(), "adios") == 0, 
              "Asignación por movimiento entre cadenas: "
              "la cadena destino debería contener una cadena "
              "igual a la de la derecha del igual.");
    fct_xchk(a.length() == 5, 
              "Asignación por movimiento entre cadenas: "
              "la longitud de la cadena a la izquierda del igual debería "
              "ser igual a la que tenía la de la derecha del igual.");
    fct_xchk(b.operator const char*() != c, 
              "Asignación por movimiento entre cadenas: el operador "
              "const char*() de la cadena a la derecha del igual debería "
              "devolver una dirección diferente de la previa al movimiento.");
    fct_xchk(b.length() == strlen(b.operator const char *()), 
              "Asignación por movimiento entre cadenas: "
              "la cadena a la derecha del igual debe quedar con una longitud "
              "igual al número de caracteres que contiene.");
    Cadena d;
    a = std::move(d);
    fct_xchk(a.operator const char*() == d.operator const char*(), 
              "Asignación por movimiento de una cadena vacía a la derecha "
              "del igual: el operador const char*() de la cadena a la izquierda "
              "del igual debería devolver la dirección de bajo nivel de la cadena "
              "a la derecha del igual, tras la asignación por movimiento.");
    fct_xchk(strcmp(a.operator const char*(), "") == 0, 
              "Asignación por movimiento de una cadena vacía a la derecha "
              "del igual: la cadena destino debería contener una cadena "
              "igual a (\"\").");
    fct_xchk(a.length() == 0, 
              "Asignación por movimiento de una cadena vacía a la derecha "
              "del igual: la longitud de la cadena a la izquierda del igual "
              "debería ser igual a %d.", 0);
    fct_xchk(d.length() == strlen(d.operator const char *()), 
              "Asignación por movimiento desde una cadena vacía a la derecha "
              "del igual: la cadena a la derecha del igual debe quedar con "
              "una longitud igual al número de caracteres que contiene.");
  }
  FCT_TEST_END();
#endif

  FCT_TEST_BGN(Cadena - Asignar una cadena de bajo nivel) {
    Cadena a(4);
    const char* c = a.operator const char*();
    a = c;
    fct_xchk(strcmp(a.operator const char*(), "    ") == 0,
              "Asignación de la propia cadena de bajo nivel: "
              "la cadena no debería cambiar de contenido.");
    fct_xchk(a.length() == 4, 
              "Asignación de la propia cadena de bajo nivel: "
              "la cadena no debería cambiar de longitud.");
    fct_xchk(a.operator const char*() == c, 
              "Asignación de la propia cadena de bajo nivel: "
              "la dirección del operador const char*() de la "
              "cadena no debería cambiar.");
    a = "lembas";
    fct_xchk(strcmp(a.operator const char*(), "lembas") == 0, 
              "Asignación desde una cadena de bajo nivel: "
              "el contenido de la cadena destino no coincide con el contenido "
              "de la cadena de bajo nivel a la derecha del igual.");
    fct_xchk(a.length() == 6, 
              "Asignación desde una cadena de bajo nivel: "
              "la longitud de la cadena a la izquierda del igual debería ser igual "
              "a la que tenía la de la derecha del igual.");
    const char* b = "";
    a = b;
    fct_xchk(strcmp(a.operator const char*(), "") == 0, 
              "Asignación desde una cadena de bajo nivel vacía: "
              "el contenido de la cadena destino no coincide con el contenido "
              "de la cadena de bajo nivel a la derecha del igual.");
    fct_xchk(a.length() == 0, 
              "Asignación desde una cadena de bajo nivel vacía: "
              "la longitud de la cadena a la izquierda del igual debería ser igual "
              "a la que tenía la de la derecha del igual.");
    fct_xchk(a.operator const char*() != b, 
              "Asignación desde una cadena de bajo nivel vacía: "
              "el operador const char*() aplicado a la cadena a la izquierda del "
              "igual debe apuntar a una cadena distinta de la de bajo de nivel a "
              "la derecha del igual."); 
  }
  FCT_TEST_END();

// Valgrind interfiere con prlimit. Las siguiente pruebas de memoria emplean
// prlimit para reducir la memoria disponible para el proceso y forzar el
// lanzamiento de la excepción std::bad_alloc en las funciones miembro
// modificadoras que pueden lanzar bad_alloc.
  
#ifndef VALGRIND
  // FCT_TEST_BGN(Cadena - Asignar una cadena de bajo nivel: memoria no disponible) {
  //   rlimit ant, nuevo{1536 * 1024, 1536 * 1024}; // máx. memoria disponible 1,5 MiB
  //   if (prlimit(0, RLIMIT_DATA, &nuevo, &ant) == 0) {
  //     Cadena c(3, '+');
  //     const char* d = c.operator const char*();
  //     vector<Cadena> vcad;
  //     try {
  //       while(true)
  //         vcad.push_back(Cadena(1023, '@'));
  //     } catch (bad_alloc&) {}
  //     try {
  //       c = vcad[0].operator const char *();
  //     } catch (bad_alloc&) {
  //       fct_xchk(strcmp(c.operator const char*(), "+++") == 0, 
  //                 "Asignación de cadena de bajo nivel: memoria insuficiente "
  //                 "('std::bad_alloc'). La cadena destino no debería cambiar de "
  //                 "contenido.");
  //       fct_xchk(c.length() == 3,
  //                 "Asignación de cadena de bajo nivel: memoria insuficiente "
  //                 "('std::bad_alloc'). La cadena destino no debería cambiar de "
  //                 "longitud.");
  //       fct_xchk(c.operator const char *() == d,
  //                 "Asignación de cadena de bajo nivel: memoria insuficiente "
  //                 "('std::bad_alloc'). El operador const char*() de la cadena "
  //                 "destino no debería devolver una dirección diferente.");
  //     }
  //     prlimit(0, RLIMIT_DATA, &ant, nullptr);
  //   }    
  //   else
  //     cerr << "\n   Test no realizado: error de limitación de memoria.\n";
  // }
  // FCT_TEST_END();
#endif

  FCT_TEST_BGN(Cadena - Observadora de longitud) {
    const Cadena a;
    fct_xchk(a.length() == 0, 
              "Observadora de longitud de cadena vacía: "
              "el valor devuelto debe ser igual a 0");
    const char *s = "Pimienta, sal y cebolla cuando se pone la olla";
    const Cadena b(s);
    fct_xchk(b.length() == strlen(s), 
              "Observadora de longitud de cadena no vacía: "
              "el valor devuelto debe ser igual a %d.", strlen(s));
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Cadena - Observadora: operator const char*()) {
    const Cadena a, b("La avaricia rompe el saco");
    fct_xchk(strcmp(a.operator const char*(), "") == 0, 
              "Operador const char*() de cadena vacía: "
              "se espera que el contenido de la cadena sea \"\".");
    fct_xchk(strcmp(b.operator const char*(), "La avaricia rompe el saco") == 0, 
              "Operador const char*() de cadena no vacía: "
              "el contenido de la cadena no corresponde con el esperado.");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Cadena - Concatenacion: con +=) {
    Cadena a("Ingles,"); // Inglés, pero para que no haya problemas
    // ni diplomáticos ni de codificaciones de caracteres...
    const Cadena b(" pirata es");
    a += b;
    fct_xchk(strcmp(a.operator const char*(), "Ingles, pirata es") == 0, 
              "Concatenación con += : "
              "el contenido de la cadena no corresponde con el esperado.");
    fct_xchk(a.length() == strlen("Ingles, pirata es"), 
              "Concatenación con += : "
              "la longitud de la cadena formada con la concatenación "
              "no es la esperada.");
    a = "A hacer y deshacer";
    a.operator +=(" llaman aprender"); // a += Cadena(" llaman aprender");
    fct_xchk(strcmp(a.operator const char*(), 
                    "A hacer y deshacer llaman aprender") == 0, 
              "Concatenación con += : "
              "el contenido de la cadena no corresponde con lo que "
              "se esperaba.");
    fct_xchk(a.length() == strlen("A hacer y deshacer llaman aprender"), 
              "Concatenación con += : "
              "la longitud de la cadena formada con la concatenación "
              "no es la esperada.");
  }
  FCT_TEST_END();

// Valgrind interfiere con prlimit. Las siguiente pruebas de memoria emplean
// prlimit para reducir la memoria disponible para el proceso y forzar el
// lanzamiento de la excepción std::bad_alloc en las funciones miembro
// modificadoras que pueden lanzar bad_alloc.
  
// #ifndef VALGRIND
//   FCT_TEST_BGN(Cadena - Concatenacion: con += (memoria no disponible)) {
//     rlimit ant, nuevo{1536 * 1024, 1536 * 1024}; // máx. memoria disponible 1,5 MiB
//     if (prlimit(0, RLIMIT_DATA, &nuevo, &ant) == 0) {
//       Cadena a(3);
//       const char* c = a.operator const char*();
//       vector<Cadena> vcad;
//       try {
//         while(true)
//           vcad.push_back(Cadena(1023, '@'));
//       } catch (bad_alloc&) {}
//       try {
//         a += vcad[0];
//       } catch (bad_alloc&) {
//         fct_xchk(strcmp(a.operator const char*(), "   ") == 0, 
//                   "Concatenación con +=: memoria insuficiente "
//                   "('std::bad_alloc'). La cadena destino no debería cambiar de "
//                   "contenido.");
//         fct_xchk(a.length() == 3,
//                   "Concatenación con +=: memoria insuficiente "
//                   "('std::bad_alloc'). La cadena destino no debería cambiar de "
//                   "longitud.");
//         fct_xchk(a.operator const char *() == c,
//                   "Concatenación con +=: memoria insuficiente "
//                   "('std::bad_alloc'). El operador const char*() de la cadena "
//                   "destino no debería devolver una dirección diferente.");
//       }
//       prlimit(0, RLIMIT_DATA, &ant, nullptr);
//     }    
//     else
//       cerr << "\n   Test no realizado: error de limitación de memoria.\n";
//   }
//   FCT_TEST_END();
// #endif

  FCT_TEST_BGN(Cadena - Concatenacion: con +) {
    const Cadena a("Cada cual,"), b(" en su corral");
    Cadena c(a + b);
    fct_xchk(strcmp((a + b).operator const char*(), 
                    "Cada cual, en su corral") == 0, 
              "Concatenación con + : "
              "el resultado de la operación no corresponde "
              "con la cadena esperada.");
    fct_xchk(c.length() == a.length() + b.length(), 
              "Concatenación con + : "
              "la longitud de la cadena formada con la concatenación "
              "no es la esperada.");
    const Cadena d("Hay más días"), e(" que longanizas");
    c = operator +(d, e); // Cadena c = d + e;
    fct_xchk(strcmp((d + e).operator const char*(), 
                    "Hay más días que longanizas") == 0, 
              "Concatenación con + : "
              "el resultado de la operación no corresponde "
              "con la cadena esperada.");
    fct_xchk(c.length() == d.length() + e.length(), 
              "Concatenación con + : "
              "la longitud de la cadena formada con la concatenación "
              "no es la esperada.");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Cadena - Comparacion: igualdad) {
    fct_xchk(Cadena("hola") == "hola", 
              "Comparación == : "
              "falla para el caso de objeto cadena y cadena de bajo nivel "
              "coincidentes.");
    fct_xchk(!("hola" == Cadena("adios")), 
              "Comparación == : "
              "falla para el caso de objeto cadena y cadena de bajo nivel "
              "no coincidentes.");
    fct_xchk(!(Cadena("hola") == Cadena("holas")), 
              "Comparación == : "
              "falla para el caso de dos objetos cadena no coincidentes.");
    fct_xchk(!(Cadena("holas") == Cadena("hola")), 
              "Comparación == : "
              "falla para el caso de dos objetos cadena no coincidentes.");
    fct_xchk(Cadena() == "", 
              "Comparación == : "
              "falla para el caso de objeto cadena y "
              "cadena de bajo nivel, ambas vacías.");
    fct_xchk(!("" == Cadena("adios")), 
              "Comparación == : "
              "falla para el caso de objeto cadena y cadena de bajo nivel "
              "no coincidentes.");
    fct_xchk(!(Cadena("adios") == Cadena()), 
              "Comparación == : "
              "falla para el caso de dos objetos cadena no coincidentes.");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Cadena - Comparacion: desigualdad) {
    fct_xchk(!(       "hola"   != Cadena("hola")), 
              "Comparación != : "
              "falla para el caso de objeto cadena y cadena de bajo nivel "
              "coincidentes.");
    fct_xchk(Cadena("hola") !=        "adios", 
              "Comparación != : "
              "falla para el caso de objeto cadena y cadena de bajo nivel "
              "no coincidentes.");
    fct_xchk(Cadena("hola") != Cadena("holas"), 
              "Comparación != : "
              "falla para el caso de dos objetos cadena no coincidentes.");
    fct_xchk(Cadena("holas") != Cadena("hola"), 
              "Comparación != : "
              "falla para el caso de dos objetos cadena no coincidentes.");
    fct_xchk(!(Cadena() != ""), 
              "Comparación != : "
              "falla para el caso de objeto cadena y "
              "cadena de bajo nivel, ambas vacías.");
    fct_xchk("" != Cadena("adios"), 
              "Comparación != : "
              "falla para el caso de objeto cadena y "
              "cadena de bajo nivel no coincidentes.");
    fct_xchk(Cadena("adios") != Cadena(), 
              "Comparación != : "
              "falla para el caso de dos objetos cadena no coincidentes.");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Cadena - Comparacion: menor que) {
    fct_xchk(  Cadena( "" ) <        "x"   ,
              "Comparación < : "
              "falla para el caso de objeto cadena vacía "
              "y cadena de bajo nivel no vacía.");
    fct_xchk(         "a"   < Cadena("b" ), 
              "Comparación < : "
              "falla para el caso de objeto cadena y cadena de bajo nivel "
              "no vacías.");
    fct_xchk(!(Cadena(    ) <         ""  ), 
              "Comparación < : "
              "falla para el caso de objeto cadena y cadena de bajo nivel "
              "vacías.");
    fct_xchk(!(Cadena("a" ) < Cadena( "" )), 
              "Comparación < : "
              "falla para el caso de dos objetos cadena, uno no vacío y "
              "otro vacío.");
    fct_xchk(!(Cadena("ab") < Cadena("ab")), 
              "Comparación < : "
              "falla para el caso de dos objetos cadena coincidentes.");
    fct_xchk(!(Cadena("ca") < Cadena("aa")), 
              "Comparación < : "
              "falla para el caso de dos objetos cadena no coincidentes.");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Cadena - Comparacion: menor o igual que) {
    fct_xchk(          ""   <= Cadena("x" ), 
              "Comparación <= : "
              "falla para el caso de objeto cadena vacía "
              "y cadena de bajo nivel no vacía.");
    fct_xchk(  Cadena("a" ) <=        "b"   ,
              "Comparación <= : "
              "falla para el caso de objeto cadena "
              "y cadena de bajo nivel no vacías.");
    fct_xchk(  Cadena("ab") <= Cadena("ab"), 
              "Comparación <= : "
              "falla para el caso de dos objetos cadena coincidentes.");
    fct_xchk(  Cadena(    ) <=        ""    , 
              "Comparación <= : "
              "falla para el caso de objeto cadena "
              "y cadena de bajo nivel vacías.");
    fct_xchk(!(Cadena("a" ) <= Cadena(    )), 
              "Comparación <= : "
              "falla para el caso de dos objetos cadena, uno no vacío y "
              "otro vacío.");
    fct_xchk(!(Cadena("ca") <=        "aa" ), 
              "Comparación <= : "
              "falla para el caso de objeto cadena y cadena de bajo nivel "
              "no vacías.");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Cadena - Comparacion: mayor que) {
    fct_xchk(!(Cadena( "" ) >        "x"  ), 
              "Comparación > : "
              "falla para el caso de objeto cadena vacía "
              "y cadena de bajo nivel no vacía.");
    fct_xchk(!(       "a"   > Cadena("b" )), 
              "Comparación > : "
              "falla para el caso de objeto cadena "
              "y cadena de bajo nivel no vacías.");
    fct_xchk(!(Cadena(    ) > Cadena( "" )), 
              "Comparación > : "
              "falla para el caso de dos objetos cadena, "
              "creados repectivamente sin parámetros uno, "
              "y el otro a partir de una cadena de bajo nivel vacía.");
    fct_xchk(!(Cadena("ab") > Cadena("ab")), 
              "Comparación > : "
              "falla para el caso de dos objetos cadena coincidentes.");
    fct_xchk(  Cadena("a" ) >         ""   , 
              "Comparación > : "
              "falla para el caso de objeto cadena y cadena de bajo nivel, "
              "no vacía y vacía respectivamente.");
    fct_xchk(  Cadena("ca") > Cadena("aa"), 
              "Comparación > : "
              "falla para el caso de dos objetos cadena no coincidentes.");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Cadena - Comparacion: mayor o igual que) {
    fct_xchk(!(        ""   >= Cadena("x" )), 
              "Comparación >= : "
              "falla para el caso de cadena de bajo nivel vacía "
              "y objeto cadena no vacía.");
    fct_xchk(!(Cadena("a" ) >=        "b" ), 
              "Comparación >= : "
              "falla para el caso de objeto cadena y cadena de bajo nivel "
              "no vacías.");
    fct_xchk(  Cadena("ab") >= Cadena("ab"), 
              "Comparación >= : "
              "falla para el caso de dos objetos cadena coincidentes.");
    fct_xchk(  Cadena(    ) >= Cadena( "" ), 
              "Comparación >= : "
              "falla para el caso de dos objetos cadena, "
              "creados repectivamente sin parámetros uno, "
              "y el otro a partir de una cadena de bajo nivel vacía.");
    fct_xchk(  Cadena("a" ) >=         "" , 
              "Comparación >= : "
              "falla para el caso de objeto cadena y cadena de bajo nivel, "
              "no vacía y vacía respectivamente.");
    fct_xchk(  Cadena("ca") >= Cadena("aa"), 
              "Comparación >= : "
              "falla para el caso de dos objetos cadena no coincidentes.");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Cadena - Leer caracter: [] y posicion valida) {
    const Cadena a("abcd");
    fct_xchk(a.operator[](0) == 'a', 
              "Lectura con [] en posición válida: "
              "el contenido devuelto no es el esperado.");
    fct_xchk(a.operator[](3) == 'd', 
              "Lectura con [] en posición válida: "
              "el contenido devuelto no es el esperado.");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Cadena - Leer caracter: [] y posicion no valida) {
    const Cadena a;
    const Cadena b("abcd");
    fct_xchk(a.operator[](0) == 0, 
              "Lectura con [] en posición no válida: "
              "el resultado de la operación no es el esperado.");
    fct_xchk(b.operator[](4) == 0, 
              "Lectura con [] en posición no válida: "
              "el resultado de la operación no es el esperado.");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Cadena - Leer caracter: at y posicion valida) {
    const Cadena a("abcd");
    fct_xchk(a.at(0) == 'a', 
              "Lectura con at( ) en posición válida: "
              "el contenido devuelto no es el esperado.");
    fct_xchk(a.at(3) == 'd', 
              "Lectura con at( ) en posición válida: "
              "el contenido devuelto no es el esperado.");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Cadena - Leer caracter: at y posicion no valida) {
    const Cadena a;
    const Cadena b("abcd");
    fct_xchk_ex(out_of_range&, a.at(0), 
                "Lectura con at( ) en cadena vacía en posición no válida: ");
    fct_xchk_ex(out_of_range&, b.at(4), 
                "Lectura con at( ) en posición no válida: ");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Cadena - Escribir caracter: [] y posicion valida) {
    Cadena a("pava");
    a.operator[](2) = 'p';
    fct_xchk(strcmp(a.operator const char*(), "papa") == 0, 
              "Escritura con []: "
              "la operación no produce el efecto esperado.");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Cadena - Escribir caracter: [] y posicion no valida) {
    Cadena a("pava");
    a.operator[](4) = '\0';
    fct_xchk(strcmp(a.operator const char*(), "pava") == 0, 
              "Escritura con []: "
              "la operación no produce el efecto esperado.");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Cadena - Escribir caracter: at() y posicion valida) {
    Cadena a("Papa");
    a.at(2) = 'c';
    fct_xchk(strcmp(a.operator const char*(), "Paca") == 0, 
              "Escritura con at( ): "
              "la operación no produce el efecto esperado.");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Cadena - Escribir caracter: at() y posicion no valida) {
    Cadena a("Papa");
    fct_xchk_ex(out_of_range&, a.at(21) = 'x', 
                "Escritura con at( ) en posición no válida: ");

    fct_xchk_ex(out_of_range&, a.at(4) = 'x', 
                "Escritura con at( ) en posición no válida: ");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Cadena - Subcadena: caso normal) {
    const Cadena a("eenie meenie moe");
    Cadena b = a.substr(6, 6);
    fct_xchk(strcmp(b.operator const char*(), "meenie") == 0, 
            "Cadena::substr(): la extracción en posición y tamaño "
            "válidos no devuelve el contenido esperado.");
    fct_xchk(b.length() == 6,
            "Cadena::substr(): la extracción en posición y tamaño "
            "válidos no devuelve una cadena de la logitud esperada.");
    b = a.substr(15, 1);
    fct_xchk(strcmp(b.operator const char*(), "e") == 0, 
            "Cadena::substr(): la extracción hasta el final "
            "de la cadena no devuelve el contenido esperado.");
    fct_xchk(b.length() == 1,
            "Cadena::substr(): la extracción hasta el final de la "
            "cadena no devuelve una cadena de la logitud esperada.");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Cadena - Subcadena: posicion inicial mayor o igual que longitud) {
    const Cadena a("0123456789");
    fct_xchk_ex(out_of_range&, a.substr(10, 10), 
              "Cadena::substr() con posición inicial igual "
              "que la longitud: ");
    fct_xchk_ex(out_of_range&, a.substr(12, 10), 
              "Cadena::substr() con posición inicial mayor "
              "que la longitud: ");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Cadena - Subcadena: posicion inicial negativa) {
    const Cadena a("0123456789");
    fct_xchk_ex(out_of_range&, a.substr(-1, 10), 
              "Cadena::substr() con posición inicial negativa: ");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Cadena - Subcadena: tamanno cero) {
    const Cadena a("eenie meenie moe");
    const Cadena b = a.substr(6, 0);
    fct_xchk(strcmp(b.operator const char*(), "") == 0, 
              "Cadena::substr(): "
              "la extracción de 0 caracteres en posición válida "
              "no devuelve el contenido esperado.");
    fct_xchk(b.length() == 0, "Cadena::substr(): la extracción de "
              "0 caracteres en posición válida no devuelve una "
              "cadena de longitud 0.");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Cadena - Subcadena: tamanno mayor que longitud restante) {
    const Cadena a("0123456789");
    fct_xchk_ex(out_of_range&, a.substr(9, 2), 
                "Cadena::substr() para tamaño mayor que la longitud restante: ");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Cadena - Subcadena: tamanno negativo) {
    const Cadena a("0123456789");
    fct_xchk_ex(out_of_range&, a.substr(9, -1), 
                "Cadena::substr() para tamaño negativo: ");
  }
  FCT_TEST_END();

  // P1 - E/S e iteradores
#ifndef P0
  FCT_TEST_BGN(Cadena - Extraccion: entrada vacia) {
    istringstream is("");
    Cadena c("algo");
    is >> c;
    fct_xchk(strcmp(c.operator const char*(), "") == 0, 
              "Extracción de entrada vacía: "
              "el contenido inyectado en la cadena no es el esperado (\"\").");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Cadena - Extraccion: solo espacios) {
    istringstream is(" \t\r\n\v");
    Cadena c("algo");
    is >> c;
    fct_xchk(strcmp(c.operator const char*(), "") == 0, 
              "Extracción de entrada sólo con espacios: "
              "el contenido inyectado en la cadena no es el esperado (\"\").");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Cadena - Extraccion: hasta fin de entrada) {
    istringstream is("prueba");
    Cadena c;
    is >> c;
    fct_xchk(strcmp(c.operator const char*(), "prueba") == 0, 
              "Extracción hasta fin de entrada: "
              "el contenido inyectado en la cadena no es el esperado.");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Cadena - Extraccion: una palabra) {
    istringstream is("bueno bonito barato");
    Cadena c;
    is >> c;
    fct_xchk(strcmp(c.operator const char*(), "bueno") == 0, 
              "Extracción de una palabra: "
              "el contenido inyectado en la cadena no es el esperado.");
    fct_xchk(is.peek() == ' ', 
              "Extracción de una palabra: "
              "tras la operación el siguiente caracter de la entrada "
              "debería ser un espacio (' ').");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Cadena - Extraccion: una palabra con espaciado inicial) {
    istringstream is("   hola adiós");
    Cadena c;
    is >> c;
    fct_xchk(strcmp(c.operator const char*(), "hola") == 0, 
              "Extracción de una palabra con espaciado inicial: "
              "el contenido inyectado en la cadena no es el esperado.");
    fct_xchk(is.peek() == ' ', 
              "Extracción de una palabra con espaciado inicial: "
              "tras la operación el siguiente caracter de la entrada "
              "debería ser un espacio (' ').");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Cadena - Extraccion: una palabra de mas de 32 caracteres) {
    istringstream is("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
    Cadena c;
    is >> c;
    fct_xchk(strcmp(c.operator const char*(), "abcdefghijklmnopqrstuvwxyzABCDEF") == 0, 
              "Extracción de una palabra con más de 32 caracteres: "
              "el contenido inyectado en la cadena no es el esperado.");
    fct_xchk(is.peek() == 'G', 
              "Extracción de una palabra con más de 32 caracteres: "
              "tras la operación el siguiente caracter de la entrada "
              "no es el esperado.");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Cadena - Insercion) {
    ostringstream os;
    const char *s = "probando 1 2 3";
    const Cadena c(s);
    os << c;
    fct_xchk(strcmp(os.str().c_str(), s) == 0, 
              "Inserción de cadena: "
              "el contenido en la salida no es el esperado.");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Cadena - Insercion nula) {
    ostringstream os;
    const Cadena c;
    os << c;
    fct_xchk(strcmp(os.str().c_str(), "") == 0, 
              "Inserción de cadena vacía: "
              "el contenido en la salida no es el esperado (\"\").");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Cadena - Iterador: begin()) {
    Cadena a("hola");
    *a.begin() = ' ';
    fct_xchk(a.begin() == a.operator const char*(), 
              "Iterador de cadena: "
              "begin() no devuelve la posición correcta.");
    fct_xchk(a[0] == ' ', 
              "Iterador de cadena: "
              "begin() no devuelve la posición correcta.");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Cadena - Iterador: end()) {
    Cadena a("hola");
    fct_xchk(a.end() == a.operator const char*() + 4, 
              "Iterador de cadena: "
              "end() no devuelve la posición correcta.");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Cadena - Iterador: begin() const) {
    const Cadena a("hola");
    fct_xchk(a.begin() == a.operator const char*(), 
              "Iterador de cadena const: "
              "begin() no devuelve la posición correcta.");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Cadena - Iterador: end() const) {
    const Cadena a("hola");
    fct_xchk(a.end() == a.operator const char*() + 4, 
              "Iterador de cadena const: "
              "end() no devuelve la posición correcta.");
  }
  FCT_TEST_END();
  FCT_TEST_BGN(Cadena - Iterador: cbegin()) {
    const Cadena a("hola");
    fct_xchk(a.cbegin() == a.operator const char*(), 
              "Iterador de cadena const: "
              "cbegin() no devuelve la posición correcta.");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Cadena - Iterador: cend()) {
    const Cadena a("hola");
    fct_xchk(a.cend() == a.operator const char*() + 4, 
              "Iterador de cadena const: "
              "cend() no devuelve la posición correcta.");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Cadena - Iterador: rbegin()/rend()) {
    Cadena a("hola");
    *a.rbegin() = 'o';
    *a.rend().base() = ' ';
    fct_xchk(*a.rbegin() == 'o', 
              "Iterador de cadena: "
              "la posición rbegin() no contiene el carácter esperado.");
    fct_xchk(*a.rend().base() == ' ', 
              "Iterador de cadena: "
              "la posición rend() no contiene el carácter esperado.");
  } FCT_TEST_END();

  FCT_TEST_BGN(Cadena - Iterador: rbegin()/rend() const) {
    const Cadena a("hola");
    fct_xchk(*a.rbegin() == 'a', 
              "Iterador de cadena const: "
              "la posición rbegin() no contiene el carácter esperado.");
    fct_xchk(*a.rend().base() == 'h', 
              "Iterador de cadena const: "
              "la posición rend() no contiene el carácter esperado.");
  } FCT_TEST_END();

  FCT_TEST_BGN(Cadena - Iterador: crbegin()/crend()) {
    const Cadena a("hola");
    fct_xchk(*a.crbegin() == 'a', 
              "Iterador de cadena const: "
              "la posición crbegin() no contiene el carácter esperado.");
    fct_xchk(*a.crend().base() == 'h', 
              "Iterador de cadena const: "
              "la posición crend() no contiene el carácter esperado.");
  } FCT_TEST_END();

  FCT_TEST_BGN(Cadena - Iteradores: recorridos directos) {
    Cadena a("hola");
    for (Cadena::iterator i = a.begin(); i != a.end(); ++i)
      (*i)++;
    fct_xchk(a == "ipmb", 
              "Iterador de cadena: "
              "el recorrido de begin() a end() modificando una cadena "
              "no la deja con el contenido esperado.");
    const Cadena b(a);
    ostringstream os;
    for (Cadena::const_iterator i = b.begin(); i != b.end(); ++i)
      os << *i;
    fct_xchk(os.str() == "ipmb", 
              "Iterador const de cadena const: "
              "el recorrido de begin() a end() sobre la cadena no presenta el "
              "contenido esperado.");
    for (auto i = a.cbegin(); i != a.cend(); ++i) os << *i;
    fct_xchk(os.str() == "ipmbipmb", 
              "Iterador de cadena const: "
              "el recorrido de cbegin() a cend() sobre la cadena no presenta el "
              "contenido esperado.");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Cadena - Iteradores: recorridos inversos) {
    const Cadena a("hola");
    Cadena b(a);
    ostringstream os;
    for (Cadena::reverse_iterator r = b.rbegin(); r != b.rend(); ++r)
      os << ++*r;
    fct_xchk(os.str() == "bmpi", 
              "Iterador inverso sobre cadena const: "
              "el recorrido de rbegin() a rend() sobre la cadena "
              "no presenta el contenido esperado.");
    for (Cadena::const_reverse_iterator r = a.rbegin(); r != a.rend(); ++r)
      os << *r;
    fct_xchk(os.str() == "bmpialoh", 
              "Iterador inverso const sobre cadena const: "
              "el recorrido de rbegin() a rend() sobre la cadena no presenta el "
              "contenido esperado.");
    for (auto r = a.crbegin(); r != a.crend(); ++r) 
      os << *r;
    fct_xchk(os.str() == "bmpialohaloh", 
              "Iterador inverso sobre cadena const: "
              "el recorrido de crbegin() a crend() sobre la cadena no presenta el "
              "contenido esperado.");
  }
  FCT_TEST_END();
#endif

#if defined(P2) || defined(P3) || defined(P4)
  FCT_TEST_BGN(Cadena - hash) {
    hash<Cadena> hc;
    size_t h = hc("hola");	// operator()
    fct_xchk(h != 0,        // 4749747280605603126
              "Hash de cadena: "
              "el valor 0 no es el esperado.");
  }
  FCT_TEST_END();
#endif
}
FCTMF_SUITE_END()
