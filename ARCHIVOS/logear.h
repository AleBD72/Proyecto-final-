int menu_principal(int op);
void cargar (tDocentes &docentes);
bool logear (tDocentes &docentes, int &posicion);
void ingresar_notas (tDocentes &docentes, tLista lista [], tNotas notas [], int& cont, int cont2, int& posicion);
void registrar_docente(tLogin &login, tDocentes &docentes);
void archivar_docentes(tDocentes docentes);