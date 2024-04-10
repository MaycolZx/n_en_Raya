#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const char EMPTY = ' ';

vector<vector<int>> encontrarPosicionesVacias(vector<vector<char>> matriz) {
  vector<vector<int>> posiciones;

  for (int fila = 0; fila < matriz.size(); fila++) {
    for (int columna = 0; columna < matriz[fila].size(); columna++) {
      if (matriz[fila][columna] == EMPTY) {
        posiciones.push_back({fila, columna});
      }
    }
  }

  return posiciones;
}
vector<vector<char>> copiar(vector<vector<char>> matriz) {
  vector<vector<char>> copia;

  for (int fila = 0; fila < matriz.size(); fila++) {
    vector<char> po;
    for (int columna = 0; columna < matriz[fila].size(); columna++) {

      po.push_back(matriz[fila][columna]);
    }
    copia.push_back(po);
  }

  return copia;
}
struct nodo {
public:
  vector<vector<char>> raya;
  vector<nodo *> next;
  int pos[2] = {0, 0};
  bool minmax;
  bool name;
  int funcion;
  int minmax_v;
  int nivel;
  nodo(bool name, bool minmax, int nivel, vector<vector<char>> raya1) {
    this->name = name;
    this->minmax = minmax;
    this->nivel = nivel;
    this->raya = copiar(raya1);
  }
};

struct arbol {
public:
  nodo *head = NULL;
  int n;
  bool name;
  int nivel;
  bool comienza;

  arbol(int n, bool name, int nivel1, bool comienza) {
    this->n = n;
    this->comienza = comienza;
    this->name = name;
    this->nivel = nivel1;
  }
  void arma_re(int &cont, nodo *head1) {
    if (head1->nivel >= nivel) {
      int k = contarFormasGanadoras('x', head1->raya, n);
      int k1 = contarFormasGanadoras('o', head1->raya, n);
      if (name) {
        head1->minmax_v = k - k1;
        // cout << k << '\n';
        // cout << k - k1 << '\n';
      } else {
        head1->minmax_v = k1 - k;
        // cout << k << '\n';
        // cout << k1-k << '\n';
      }

      return;
    } else {
      vector<vector<int>> pos = encontrarPosicionesVacias(head1->raya);
      // imprimirMatriz(head1->raya);
      // cout << pos.size() << '\n';
      if (pos.size()) {

        for (size_t i = 0; i < pos.size(); i++) {
          vector<vector<char>> temp = copiar(head1->raya);

          if (!head1->name) {
            temp[pos[i][0]][pos[i][1]] = 'x';
          } else {
            temp[pos[i][0]][pos[i][1]] = 'o';
          }
          // imprimirMatriz(temp);
          // cout << head1->name << '\n';

          nodo *temp1 =
              new nodo(!head1->name, !head1->minmax, head1->nivel + 1, temp);
          temp1->pos[0] = pos[i][0];
          temp1->pos[1] = pos[i][1];
          head1->next.push_back(temp1);
          cont++;
          // imprimirMatriz(temp);
          arma_re(cont, temp1);
        }
        if (head1->next.size() > 0) {
          vector<int> p;
          // cout << "w" << '\n';
          for (size_t i = 0; i < head1->next.size(); i++) {
            p.push_back(head1->next[i]->minmax_v);
          }
          if (head->minmax) {
            auto maximo = max_element(p.begin(), p.end());
            int max_value = (maximo != p.end()) ? *maximo : INT_MIN;
            head1->minmax_v = max_value;

          } else {
            auto minimo = min_element(p.begin(), p.end());
            int min_value = (minimo != p.end()) ? *minimo : INT_MAX;
            head1->minmax_v = min_value;
          }
        }

      } else {
        return;
      }
    }
  }

  void armar() {
    int nivelc = 0;
    head =
        new nodo(!name, 1, 0, vector<vector<char>>(n, vector<char>(n, EMPTY)));

    int cont = 0;
    arma_re(cont, head);
  }

  void imprimirArbol(nodo *node, int indent = 0) {
    if (node == nullptr)
      return;

    for (int i = 0; i < indent; ++i)
      cout << " ";

    cout << "Nivel " << node->nivel << ":" << endl;
    for (auto &row : node->raya) {
      for (int i = 0; i < indent; ++i)
        cout << " ";
      for (auto &cell : row)
        cout << cell << " ";
      cout << endl;
    }
    cout << endl;

    for (auto &child : node->next) {
      for (int i = 0; i < indent; ++i)
        cout << " ";
      cout << "|\n";
      imprimirArbol(child, indent + 4);
    }
  }

  void imprimirMatriz(vector<vector<char>> &grid) {
    int n = grid.size();

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j)
        cout << "| " << grid[i][j] << " |";

      cout << std::endl << " ";

      cout << endl;
    }
  }

  int contarFormasGanadoras(char jugador, vector<vector<char>> tablero, int n) {
    int formasGanadoras = 0;

    for (int i = 0; i < n; ++i) {
      bool x1 = false;
      bool x2 = true;
      for (int j = 0; j < n; ++j) {
        if (tablero[i][j] == jugador || tablero[i][j] == ' ') {
          x1 = true;
        } else if (tablero[i][j] != EMPTY) {
          x2 = false;
          break;
        }
      }
      if (x2 && x1)
        formasGanadoras++;
    }

    for (int j = 0; j < n; ++j) {
      bool x1 = false;
      bool x2 = true;
      for (int i = 0; i < n; ++i) {
        if (tablero[i][j] == jugador || tablero[i][j] == ' ') {
          x1 = true;
        } else if (tablero[i][j] != EMPTY) {
          x2 = false;
          break;
        }
      }
      if (x2 && x1)
        formasGanadoras++;
    }

    bool x1 = false;
    bool x2 = true;
    for (int i = 0; i < n; ++i) {
      if (tablero[i][i] == jugador || tablero[i][i] == ' ') {
        x1 = true;

      } else if (tablero[i][i] != EMPTY) {
        x2 = false;
        break;
      }
    }
    if (x2 && x1)
      formasGanadoras++;

    x1 = false;
    x2 = true;
    for (int i = 0; i < n; ++i) {
      if (tablero[i][n - 1 - i] == jugador || tablero[i][n - 1 - i] == ' ') {
        x1 = true;

      } else if (tablero[i][n - 1 - i] != EMPTY) {
        x1 = false;
        break;
      }
    }
    if (x2 && x1)
      formasGanadoras++;

    return formasGanadoras;
  }
};

bool checkWin(char player, vector<vector<char>> &grid) {
  int n = grid.size();

  // Check rows and columns
  for (int i = 0; i < n; ++i) {
    bool rowWin = true;
    bool colWin = true;
    for (int j = 0; j < n; ++j) {
      if (grid[i][j] != player)
        rowWin = false;
      if (grid[j][i] != player)
        colWin = false;
    }
    if (rowWin || colWin)
      return true;
  }

  // Check diagonals
  bool mainDiagWin = true;
  bool antiDiagWin = true;
  for (int i = 0; i < n; ++i) {
    if (grid[i][i] != player)
      mainDiagWin = false;
    if (grid[i][n - 1 - i] != player)
      antiDiagWin = false;
  }
  if (mainDiagWin || antiDiagWin)
    return true;

  return false; // No win
}

int main() {
  int nxn, profundidad, primero;
  cout << "--------- N en raya -----------" << endl
       << "Ingrese el valor de n: ";
  cin >> nxn;

  cout << endl;

  cout << "Ingrese la profundidad del arbol: ";
  cin >> profundidad;

  cout << "Quieres ir primero o segundo (1: primero   2: segundo)";
  cin >> primero;
  // arbol(int n, bool name, int nivel1, bool comienza)
  arbol ar(nxn, 1, profundidad, 1);
  ar.armar();

  int position;
  bool gameOver = false;
  char currentPlayer = 'x';
  nodo *current = ar.head;

  int x = 0, y = 0;

  ar.imprimirMatriz(ar.head->raya);
  int turno = 0;

  while (!gameOver) {
    cout << endl << "-----------------------" << endl << endl;
    cout << "Current board:" << endl << endl;
    ar.imprimirMatriz(current->raya);

    // if (turno % 2 == 0) { // turno jugador
    //  Get the next play from the current player
    cout << "Player " << currentPlayer
         << ", enter the position to make your play (from 1 to " << nxn * nxn
         << "): ";
    cin >> position;

    int row = (position - 1) / nxn;
    int col = (position - 1) % nxn;

    for (int i = 0; current->next.size(); i++) {
      if (current->next[i]->raya[row][col] == currentPlayer) {
        current = current->next[i];
        break;
      } else {
        cout << "Jugada no valida";
      }
    }

    if (checkWin(currentPlayer, current->raya)) {
      cout << "Player " << currentPlayer << " wins!" << endl;
      ar.imprimirMatriz(current->raya);
      gameOver = true;
    } else {
      // Switch to the next player
      currentPlayer = (currentPlayer == 'x') ? 'o' : 'x';
    }

    turno++;
  }

  // ar.imprimirArbol(ar.head); // Modificación aquí

  // cout << ar.head->next[4]->minmax_v;
}
