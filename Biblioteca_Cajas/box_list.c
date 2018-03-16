#ifdef _WIN32 // 2

/*-* Caja con lineas simples *-*/
const char * CAJA1[11] = {
    "\xDA", "\xBF", "\xD9", "\xC0",
    "\xC2", "\xB4", "\xC1", "\xC3",
    "\xC4", "\xB3", "\xC5"
};

/*-* Caja con lineas dobles *-*/
const char * CAJA2[11] = {
    "\xC9", "\xBB", "\xBC", "\xC8",
    "\xCB", "\xB9", "\xCA", "\xCC",
    "\xCD", "\xBA", "\xCE"
};

// La caja con esquinas redondeadas no existe en windows
// simplemente se pusieron simbolos de suma y resta en su lugar
const char * CAJA3[11] = {
    "+", "+", "+", "+",
    "+", "+", "+", "+",
    "-", "|", "+"
};

#else // 2

/*-* Caja con lIneas simples *-*/
const char * CAJA1[11] = {
    "\u250C", "\u2510", "\u2518", "\u2514",
    "\u252C", "\u2524", "\u2534", "\u251C",
    "\u2500", "\u2502", "\u253C"
};

/*-* Caja con lIneas dobles *-*/
const char * CAJA2[11] = {
    "\u2554", "\u2557", "\u255D", "\u255A",
    "\u2566", "\u2563", "\u2569", "\u2560",
    "\u2550", "\u2551", "\u256C"
};

/*-* Caja con esquinas redondeadas *-*/
const char * CAJA3[11] = {
    "\u256D", "\u256E", "\u256F", "\u2570",
    "\u252C", "\u2524", "\u2534", "\u251C",
    "\u2500", "\u2502", "\u253C"
};

#endif // Fin _WIN32 2
