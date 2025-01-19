# Driver para o SC75823 usando Arduino
A placa usada é um frontal do H-Buster **HBD-2300MP**


#### Frente
![Frente da Placa](https://github.com/lucas458/SC75823/blob/main/misc/frente.jpg?raw=true "Frente da placa")

#### Verso
![Verso da Placa](https://github.com/lucas458/SC75823/blob/main/misc/verso.jpg?raw=true "Verso da placa")


## Datasheets
[Driver do Display - SC75823](https://github.com/lucas458/SC75823/blob/main/datasheet/sc75823e_w_datasheet.pdf)



### Display de 14 Segmentos
![Display](https://github.com/lucas458/SC75823/blob/main/misc/14-segment.png?raw=true "Display 14 segmentos") 


### Tabela de mapeamento
![Tabela](https://github.com/lucas458/SC75823/blob/main/misc/SC75823.jpg?raw=true "Tabela de mapeamento")


> [!WARNING]  
> Elementos com **"*"** devem ter o valor `0`


São 156 bits que podem ser manipulados individualmente.
Ex: O semento A do digito 1 corresponde ao indice `7`

```c
displayBuffer[7] = 1; // Ligado
displayBuffer[7] = 0; // Desligado
```

### Para usar simbolos, use os **SYMBOL_xxxx** no indice do buffer:

```c
#define SYMBOL_ST         0
#define SYMBOL_FILE       12
#define SYMBOL_AF         27
#define SYMBOL_TA         42
#define SYMBOL_TP         57
#define SYMBOL_CARD       72 
#define SYMBOL_FOLDER     75
#define SYMBOL_DP         87 // Decimal Point
#define SYMBOL_PENDRIVE   120
#define SYMBOL_XBS        122
#define SYMBOL_PHONE      123
#define SYMBOL_FRAME      135
#define SYMBOL_EQ         136
#define SYMBOL_SUBW       144
#define SYMBOL_LOCAL      154
#define SYMBOL_BLUETOOTH  155
```

```c
displayBuffer[SYMBOL_BLUETOOTH] = 1; // Ligado
displayBuffer[SYMBOL_BLUETOOTH] = 0; // Desligado
```


### Para Controlar o display de 7 segmentos
```c
void setMiniDigitData(uint8_t data);
```

### Para Controlar o display de 14 segmentos
```c
void setBigDigitData(uint16_t data, uint8_t digit);
```

Os bits do parametro `data` controla cada segmento do display

> [!NOTE]  
> O segmento **A** corresponde ao bit `0` do parametro `data`


### Para Enviar String no display de 14 segmentos
```c
void setBigDigitString(char *txt);
```

> [!NOTE]  
> Nem todos os caracteres do `digitMap14[]` foram mapeados corretamente, apenas números e letras maiúsculas.



### Enviar Dados à tela
```c
void SC75823_update(uint8_t control);
```


#### DR - Drive Type: bit `1`
| Nível | Descrição |
| :-: | :-: | 
| 0 | 1/2 bias drive |
| 1 | 1/3 bias drive |


#### SC - Display State: bit `2`
| Nível | Descrição |
| :-: | :-: | 
| 0 | On |
| 1 | Off |


#### BU - Mode bit: `3`
| Nível | Descrição |
| :-: | :-: | 
| 0 | Normal Mode |
| 1 | Power-saving mode |

> [!WARNING]  
> Os demais bits devem ter o valor `0`


