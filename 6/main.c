#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 1001
#define INVALID_INPUT { printf("Invalid input.\n"); return 0; }

typedef struct {
    unsigned short m_Month;
    unsigned short m_Day;
    unsigned short m_Hour;
    unsigned short m_Minute;
} TTime;

bool equalDate(TTime a, TTime b) {
    return a.m_Month == b.m_Month
        && a.m_Day == b.m_Day
        && a.m_Hour == b.m_Hour
        && a.m_Minute == b.m_Minute;
}

bool lessDate(TTime a, TTime b) {
    if (a.m_Month != b.m_Month) return a.m_Month < b.m_Month;
    if (a.m_Day != b.m_Day) return a.m_Day < b.m_Day;
    if (a.m_Hour != b.m_Hour) return a.m_Hour < b.m_Hour;
    return a.m_Minute < b.m_Minute;
}

int maxDay(const unsigned short m_Month) {
    int day[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
    if (m_Month < 1 || m_Month > 12) return 0;
    return day[m_Month];
}

bool makeDate(int m, int d, int h, int min, TTime *date) {
    if (m < 1 || m > 12) return false;
    if (d < 1 || d > maxDay((unsigned short)m)) return false;
    if (h < 0 || h > 23) return false;
    if (min < 0 || min > 59) return false;
    date->m_Month = (unsigned short)m;
    date->m_Day = (unsigned short)d;
    date->m_Hour = (unsigned short)h;
    date->m_Minute = (unsigned short)min;
    return true;
}

typedef struct {
    unsigned *camera_id;
    unsigned capacity;
    unsigned size;
    TTime date;
} Spoted;

typedef struct {
    char rz[MAX_STR];
    Spoted *spoted;
    unsigned cap; 
    unsigned size;
} TCar;

char decoder[][4] = { "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };
int decode_month(const char *str) {
    for (int i = 0; i < 12; ++i) if (strcmp(str, decoder[i]) == 0) return i + 1;
    return 13;
}
const char *incode_month(int month) { return decoder[month - 1]; }

int parse_date(TTime *date) {
    char month[4];
    int day, hour, minute;
    char sign;
    if (scanf(" %3s", month) != 1) return 0;
    int month_num = decode_month(month);
    if (month_num == 13) return 0;
    if (scanf(" %d", &day) != 1) return 0;
    if (scanf(" %d", &hour) != 1) return 0;
    if (scanf(" %c", &sign) != 1) return 0;
    if (sign != ':') return 0;
    if (scanf(" %d", &minute) != 1) return 0;
    if (!makeDate(month_num, day, hour, minute, date)) return 0;
    return 1;
}

typedef struct NODE {
    TCar value;
    struct NODE *left;
    struct NODE *right;
    int height;
} Node;

Node *first = NULL;

int node_height(Node *n) { return n ? n->height : 0; }
void update_height(Node *n) {
    if (!n) return;
    int hl = node_height(n->left);
    int hr = node_height(n->right);
    n->height = (hl > hr ? hl : hr) + 1;
}
int balance_factor(Node *n) {
    if (!n) return 0;
    return node_height(n->left) - node_height(n->right);
}

Node *rotate_right(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;
    x->right = y;
    y->left = T2;
    update_height(y);
    update_height(x);
    return x;
}

Node *rotate_left(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;
    y->left = x;
    x->right = T2;
    update_height(x);
    update_height(y);
    return y;
}

Spoted *alloc_spoted_array(unsigned cap) {
    Spoted *arr = ( Spoted * ) calloc(cap, sizeof(Spoted));
    return arr;
}

Node *createNode(const char *str) {
    Node *newNode = ( Node * ) malloc(sizeof(Node));

    strncpy(newNode->value.rz, str, MAX_STR - 1);
    newNode->value.rz[MAX_STR - 1] = '\0';

    newNode->value.cap = 1; 
    newNode->value.size = 0;
    newNode->value.spoted = alloc_spoted_array(newNode->value.cap);

    newNode->left = newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

Node *insertAVL(Node *node, const char *key, Node **result) {
    if (node == NULL) {
        *result = createNode(key);
        return *result;
    }
    int cmp = strcmp(key, node->value.rz);
    if (cmp < 0) {
        node->left = insertAVL(node->left, key, result);
    } else if (cmp > 0) {
        node->right = insertAVL(node->right, key, result);
    } else {
        *result = node;
        return node;
    }

    update_height(node);
    int bf = balance_factor(node);

    if (bf > 1 && strcmp(key, node->left->value.rz) < 0) return rotate_right(node);
    if (bf < -1 && strcmp(key, node->right->value.rz) > 0) return rotate_left(node);
    if (bf > 1 && strcmp(key, node->left->value.rz) > 0) {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }
    if (bf < -1 && strcmp(key, node->right->value.rz) < 0) {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    return node;
}

Node *findAVL(Node *node, const char *key) {
    if (!node) return NULL;
    int cmp = strcmp(key, node->value.rz);
    if (cmp < 0) return findAVL(node->left, key);
    if (cmp > 0) return findAVL(node->right, key);
    return node;
}

void deleteSpoted(Node *root) {
    if (!root) return;
    for (unsigned i = 0; i < root->value.size; ++i) {
        if (root->value.spoted[i].camera_id) free(root->value.spoted[i].camera_id);
    }
    if (root->value.spoted) free(root->value.spoted);
}

void deleteAVL(Node *root) {
    if (!root) return;
    deleteAVL(root->left);
    deleteAVL(root->right);
    deleteSpoted(root);
    free(root);
}

unsigned binarySearch(const TCar *curr, const TTime date) {
    if (curr->size == 0) return 0;
    int lo = 0;
    int hi = (int)curr->size - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (lessDate(date, curr->spoted[mid].date)) hi = mid - 1;
        else if (lessDate(curr->spoted[mid].date, date)) lo = mid + 1;
        else return (unsigned)mid; 
    }
    return (unsigned)lo; 
}

void insertSort(Spoted *cell, unsigned indx, TCar *curr) {
    int i = curr->size - 1;
    for (; i >= (int)indx; --i) curr->spoted[i + 1] = curr->spoted[i];
    curr->spoted[indx] = *cell;
    curr->size++;
}

void insertCam ( unsigned camera_id, Spoted * curr ) {
    int i = curr->size - 1;
	for (; i >= 0 && curr -> camera_id [ i ] > camera_id; i -- )
		curr -> camera_id [ i + 1 ] = curr -> camera_id [ i ];
	curr -> camera_id [ i + 1 ] = camera_id;
	curr -> size ++;
}

void insertSpoted(TCar *curr, TTime date, unsigned camera_id) {
    if (curr->cap <= curr->size) {
        unsigned newcap = curr->cap ? curr->cap * 2u : 1u;
        Spoted *tmp = ( Spoted * ) realloc(curr->spoted, newcap * sizeof(Spoted));
        for (unsigned i = curr->cap; i < newcap; ++i) {
            tmp[i].camera_id = NULL;
            tmp[i].capacity = 0;
            tmp[i].size = 0;
        }
        curr->spoted = tmp;
        curr->cap = newcap;
    }

    unsigned indx = binarySearch(curr, date);

    if (indx < curr->size && equalDate(curr->spoted[indx].date, date)) {
        Spoted *s = &curr->spoted[indx];
        if (s->capacity <= s->size) {
            unsigned newc = s->capacity ? s->capacity * 2u : 1u;
            unsigned *tmp = ( unsigned * )realloc(s->camera_id, newc * sizeof(unsigned));
            s->camera_id = tmp;
            s->capacity = newc;
        }
		insertCam(camera_id, s);
    } else {
        Spoted cell;
        cell.camera_id = ( unsigned * )malloc(sizeof(unsigned));
        cell.camera_id[0] = camera_id;
        cell.capacity = 1;
        cell.size = 1;
        cell.date = date;
        insertSort(&cell, indx, curr);
    }
}

void insertRZ(const char *rz, TTime date, int camera_id) {
    Node *curr = NULL;
    first = insertAVL(first, rz, &curr);
    insertSpoted(&curr->value, date, (unsigned)camera_id);
}

void result_out(const Spoted *spoted) {
    printf("%s %d %02d:%02d, ", incode_month(spoted->date.m_Month),
           spoted->date.m_Day,
           spoted->date.m_Hour,
           spoted->date.m_Minute);
    printf("%ux [", spoted->size);
    for (unsigned i = 0; i < spoted->size; ++i) {
        printf("%d", spoted->camera_id[i]);
        if (i + 1 != spoted->size) printf(", ");
    }
    printf("]\n");
}

void findResult(TTime date, const char *rz) {
    Node *curr = findAVL(first, rz);
    if (!curr) {
        printf("> Car not found.\n");
        return;
    }
    unsigned pos = binarySearch(&curr->value, date);
    if (pos < curr->value.size && equalDate(curr->value.spoted[pos].date, date)) {
        printf("> Exact: ");
        result_out(&curr->value.spoted[pos]);
        return;
    }

    printf("> Previous: ");
    if (pos == 0 && curr->value.size == 0) {
        printf("N/A\n");
    } else if (pos == 0 && lessDate(date, curr->value.spoted[0].date)) {
        printf("N/A\n");
    } else {
        unsigned idx = (pos == 0) ? 0 : pos - 1;
        result_out(&curr->value.spoted[idx]);
    }

    printf("> Next: ");
    if (pos >= curr->value.size) {
        printf("N/A\n");
    } else {
        result_out(&curr->value.spoted[pos]);
    }
}

int parse_reports(void) {
    char c;
    char rz[MAX_STR];
    TTime date;
    int camera_id;

    if (scanf(" %c", &c) != 1) INVALID_INPUT;
    if (c != '{') INVALID_INPUT;

    int ch;
    do {
        ch = getchar();
        if (ch == EOF) INVALID_INPUT;
    } while (isspace(ch));
    if (ch == '}') {
        INVALID_INPUT;
    }
    ungetc(ch, stdin);

    while (1) {
        if (scanf(" %d", &camera_id) != 1) INVALID_INPUT;
        if (camera_id < 0) INVALID_INPUT;
        char sign;
        if (scanf(" %c", &sign) != 1) INVALID_INPUT;
        if (sign != ':') INVALID_INPUT;
        if (scanf(" %1000s", rz) != 1) INVALID_INPUT;
        if (!parse_date(&date)) INVALID_INPUT;
        if (scanf(" %c", &sign) != 1) INVALID_INPUT;
        if (sign != ',' && sign != '}') INVALID_INPUT;

        insertRZ(rz, date, camera_id);

        if (sign == '}') break;
    }
    return 1;
}

int main(void) {
    printf("Camera reports:\n");
    if (!parse_reports()) return 0;
    printf("Search:\n");
    TTime input_date;
    char input_string[MAX_STR];

	while (1) {
        int r = scanf(" %1000s", input_string);
        if (r == EOF) break;
        if (r != 1) { deleteAVL(first); INVALID_INPUT; }
        if (!parse_date(&input_date)) { deleteAVL(first); INVALID_INPUT; }
        findResult(input_date, input_string);
    }

    deleteAVL(first);
    return 0;
}

