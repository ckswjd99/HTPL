#include "../htpl.h"

value* valueNEG(value* v1) {
    if(v1->type == _NUMBER) {
        value* temp = (value*)malloc(sizeof(value));
        temp->type = _NUMBER;
        temp->number = -(v1->number);
        return temp;
    }
    else if(v1->type == _TEXT) {
        printError("unexpected type(text) for negation");
        return NULL;
    }
    else {
        printError("unexpected type(unknown) for negation");
        return NULL;
    }
}

value* valueNOT(value* v1) {
    if(v1->type == _NUMBER) {
        value* temp = (value*)malloc(sizeof(value));
        temp->type = _NUMBER;
        temp->number = !(v1->number);
        return temp;
    }
    else if(v1->type == _TEXT) {
        printError("unexpected type(text) for not operation");
        return NULL;
    }
    else {
        printError("unexpected type(unknown) for not operation");
        return NULL;
    }
}

value* valueOR(value* v1, value* v2) {
    if(v1->type == _NUMBER && v2->type == _NUMBER) {
        value* temp = (value*)malloc(sizeof(value));
        temp->type = _NUMBER;
        temp->number = v1->number || v2->number;
        return temp;
    }
    else if(v1->type == _TEXT) {
        printError("unexpected type(text) of first operand for or operation");
        return NULL;
    }
    else if(v2->type == _TEXT) {
        printError("unexpected type(text) of second operand for or operation");
        return NULL;
    }
    else {
        printError("unexpected type(unknown) for or operation");
        return NULL;
    }
}

value* valueAND(value* v1, value* v2) {
    if(v1->type == _NUMBER && v2->type == _NUMBER) {
        value* temp = (value*)malloc(sizeof(value));
        temp->type = _NUMBER;
        temp->number = v1->number && v2->number;
        return temp;
    }
    else if(v1->type == _TEXT) {
        printError("unexpected type(text) of first operand for and operation");
        return NULL;
    }
    else if(v2->type == _TEXT) {
        printError("unexpected type(text) of second operand for and operation");
        return NULL;
    }
    else {
        printError("unexpected type(unknown) for and operation");
        return NULL;
    }
}

value* valueComp(value* v1, value* v2, int type) {
    // type check
    if(v1->type == _NUMBER && v2->type == _NUMBER) {
    }
    else if(v1->type == _TEXT) {
        printError("unexpected type(text) of first operand for and operation");
        return NULL;
    }
    else if(v2->type == _TEXT) {
        printError("unexpected type(text) of second operand for and operation");
        return NULL;
    }
    else {
        printError("unexpected type(unknown) for and operation");
        return NULL;
    }

    // value operation
    if(type == _BIGGER) {
        value* temp = (value*)malloc(sizeof(value));
        temp->type = _NUMBER;
        temp->number = v1->number > v2->number;
        return temp;
    }
    else if(type == _LESS) {
        value* temp = (value*)malloc(sizeof(value));
        temp->type = _NUMBER;
        temp->number = v1->number < v2->number;
        return temp;
    }
    else if(type == _SAME) {
        value* temp = (value*)malloc(sizeof(value));
        temp->type = _NUMBER;
        temp->number = v1->number == v2->number;
        return temp;
    }
    else {
        printError("unexpected type of comparison operation");
        return NULL;
    }
}

value* valueBinOp(value* v1, value* v2, int type) {
    char buf[512];
    if(type == _PLUS) {
        if(v1->type == _NUMBER && v2->type == _NUMBER) {
            value* temp = (value*)malloc(sizeof(value));
            temp->type = _NUMBER;
            temp->number = v1->number + v2->number;
            return temp;
        }
        else if(v1->type == _NUMBER && v2->type == _TEXT) {
            value* temp = (value*)malloc(sizeof(value));
            temp->type = _TEXT;
            sprintf(buf, "%d", v1->number);
            strcat(buf, v2->text);
            temp->text = strdup(buf);
            return temp;
        }
        else if(v1->type == _TEXT && v2->type == _NUMBER) {
            value* temp = (value*)malloc(sizeof(value));
            temp->type = _TEXT;
            sprintf(buf, "%d", v2->number);
            strcpy(buf + strlen(buf), buf);
            strcpy(buf, v1->text);
            temp->text = strdup(buf);
            return temp;
        }
        else if(v1->type == _TEXT && v2->type == _TEXT) {
            value* temp = (value*)malloc(sizeof(value));
            temp->type = _TEXT;
            strcpy(buf, v1->text);
            strcat(buf, v2->text);
            temp->text = strdup(buf);
            return temp;
        }
        else {
            printError("unexpected type(unknown) for plus operation");
            return NULL;
        }
    }
    else if(type == _MINUS) {
        if(v1->type == _NUMBER && v2->type == _NUMBER) {
            value* temp = (value*)malloc(sizeof(value));
            temp->type = _NUMBER;
            temp->number = v1->number + v2->number;
            return temp;
        }
        else if(v1->type == _TEXT) {
            printError("unexpected type(text) of first operand for minus operation");
            return NULL;
        }
        else if(v2->type == _TEXT) {
            printError("unexpected type(text) of second operand for minus operation");
            return NULL;
        }
        else {
            printError("unexpected type(unknown) of plus operation");
            return NULL;
        }
    }
    else if(type == _MULT) {
        if(v1->type == _NUMBER && v2->type == _NUMBER) {
            value* temp = (value*)malloc(sizeof(value));
            temp->type = _NUMBER;
            temp->number = v1->number * v2->number;
            return temp;
        }
        else if(v1->type == _TEXT) {
            printError("unexpected type(text) of first operand for minus operation");
            return NULL;
        }
        else if(v2->type == _TEXT) {
            printError("unexpected type(text) of second operand for minus operation");
            return NULL;
        }
        else {
            printError("unexpected type(unknown) of plus operation");
            return NULL;
        }
    }
    else if(type == _DIVIDE) {
        if(v1->type == _NUMBER && v2->type == _NUMBER) {
            if(v2->number == 0) {
                printError("divide by zero");
                return NULL;
            }
            value* temp = (value*)malloc(sizeof(value));
            temp->type = _NUMBER;
            temp->number = v1->number / v2->number;
            return temp;
        }
        else if(v1->type == _TEXT) {
            printError("unexpected type(text) of first operand for minus operation");
            return NULL;
        }
        else if(v2->type == _TEXT) {
            printError("unexpected type(text) of second operand for minus operation");
            return NULL;
        }
        else {
            printError("unexpected type(unknown) of plus operation");
            return NULL;
        }
    }
    else {
        printError("unexpected type of binary operation");
        return NULL;
    }
}

value* parseNumber(int raw) {
    value* temp = (value*)malloc(sizeof(value));
    temp->type = _NUMBER;
    temp->number = raw;
    return temp;
}

value* parseText(char* raw) {
    value* temp = (value*)malloc(sizeof(value));
    temp->type = _TEXT;
    temp->text = strdup(raw);
    return temp;
}