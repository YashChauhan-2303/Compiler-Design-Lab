#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int action[12][6] = {
//   id   +    *    (    )    $
    {  5,  0,  0,  4,  0,  0 }, // 0
    {  0,  6,  0,  0,  0, 99 }, // 1
    {  0, -2,  7,  0, -2, -2 }, // 2
    {  0, -4, -4,  0, -4, -4 }, // 3
    {  5,  0,  0,  4,  0,  0 }, // 4
    {  0, -6, -6,  0, -6, -6 }, // 5
    {  5,  0,  0,  4,  0,  0 }, // 6
    {  5,  0,  0,  4,  0,  0 }, // 7
    {  0,  6,  0,  0, 11,  0 }, // 8
    {  0, -1,  7,  0, -1, -1 }, // 9
    {  0, -3, -3,  0, -3, -3 }, // 10
    {  0, -5, -5,  0, -5, -5 }, // 11
};

int go_to[12][3] = {
//   E   T   F
    { 1,  2,  3 },
    { 0,  0,  0 },
    { 0,  0,  0 },
    { 0,  0,  0 },
    { 8,  2,  3 },
    { 0,  0,  0 },
    { 0,  9,  3 },
    { 0,  0, 10 },
    { 0,  0,  0 },
    { 0,  0,  0 },
    { 0,  0,  0 },
    { 0,  0,  0 },
};

int rule_len[]  = { 0, 3, 1, 3, 1, 3, 1 };
int rule_lhs[]  = { 0, 0, 0, 1, 1, 2, 2 };
char *rule_name[] = {
    "",
    "E -> E + T",
    "E -> T",
    "T -> T * F",
    "T -> F",
    "F -> ( E )",
    "F -> id"
};
char *token_name[] = { "id", "+", "*", "(", ")", "$" };
char *nt_name[]    = { "E", "T", "F" };

int stack[100];
int top = -1;
void push(int v) { stack[++top] = v; }
int  pop()       { return stack[top--]; }
int  peek()      { return stack[top]; }

int get_token(char c) {
    if (c == '+') return 1;
    if (c == '*') return 2;
    if (c == '(') return 3;
    if (c == ')') return 4;
    if (c == '$') return 5;
    if ((c>='a'&&c<='z')||(c>='A'&&c<='Z')||(c>='0'&&c<='9')) return 0;
    return -1;
}

void print_stack() {
    char buf[200] = "";
    for (int i = 0; i <= top; i++) {
        char tmp[20];
        if (stack[i] >= 10) {
            sprintf(tmp, "%s ", nt_name[stack[i] - 10]);
        } else {
            sprintf(tmp, "%d ", stack[i]);
        }
        strcat(buf, tmp);
    }
    printf("%-35s", buf);
}

void print_input(int *input, int pos, int inp_top) {
    char buf[200] = "";
    for (int i = pos; i < inp_top; i++) {
        strcat(buf, token_name[input[i]]);
        strcat(buf, " ");
    }
    printf("%-35s", buf);
}

int main() {
    char expr[100];
    printf("Enter expression (end with $): ");
    scanf("%s", expr);

    // tokenize
    int input[100], inp_top = 0;
    int prev_was_id = 0;
    for (int i = 0; expr[i] != '\0'; i++) {
        int t = get_token(expr[i]);
        if (t == -1) {
            printf("Invalid symbol: %c\n", expr[i]);
            return 0;
        }
        if (t == 0) {
            if (!prev_was_id) { input[inp_top++] = 0; prev_was_id = 1; }
        } else {
            input[inp_top++] = t;
            prev_was_id = 0;
        }
    }

    printf("\n%-35s %-35s %-30s\n", "Stack", "Input", "Action");
    printf("----------------------------------------"
           "----------------------------------------\n");

    push(0);
    int pos = 0;

    while (1) {
        int state = peek();
        int sym   = input[pos];

        // bounds check
        if (state < 0 || state > 11 || sym < 0 || sym > 5) {
            print_stack();
            print_input(input, pos, inp_top);
            printf("ERROR\n\n=> Rejected\n");
            break;
        }

        int act = action[state][sym];

        print_stack();
        print_input(input, pos, inp_top);

        if (act == 99) {
            printf("ACCEPT\n\n=> Accepted\n");
            break;
        } else if (act > 0) {
            printf("Shift %d\n", act);
            push(sym);
            push(act);
            pos++;
        } else if (act < 0) {
            int rule = -act;
            printf("Reduce by %s\n", rule_name[rule]);
            for (int i = 0; i < rule_len[rule]; i++) { pop(); pop(); }
            int top_state = peek();
            int lhs = rule_lhs[rule];
            int next_state = go_to[top_state][lhs];
            if (next_state == 0 && top_state != 0) {
                print_stack();
                print_input(input, pos, inp_top);
                printf("ERROR\n\n=> Rejected\n");
                break;
            }
            push(lhs + 10);
            push(next_state);
        } else {
            printf("ERROR\n\n=> Rejected\n");
            break;
        }
    }
    return 0;
}