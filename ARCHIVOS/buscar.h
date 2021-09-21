int menuBusqueda (int opg);
void busqueda_binaria (tLista lista[], int &cont,float nota, string &busqueda, int &pos, bool &f);
void busqueda_lineal (tLista lista[], int &cont, float nota, string &busqueda, int &pos, bool &f);
int interpolacion (tLista lista[], int &cont, float nota, string &busqueda);
void guardarBusqueda (float nota, tLista lista [MAX], tDocentes &docentes, string &busqueda, int &pos, bool &f, int &posicion);