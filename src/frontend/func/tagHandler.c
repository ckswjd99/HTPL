#include "../htpl.h"

void commonTagOpenHandler(tagNode* openTag) {
    char* tagName = openTag->name;
    attrNode* attrList = openTag->attr;

    if(tagName == "body") {

    }
    else if(tagName == "input") {
        attrNode* variableName = findAttrByName(attrList, "name");
        attrNode* variableType = findAttrByName(attrList, "type");
        attrNode* variableValue = findAttrByName(attrList, "value");

    }
    else if(tagName == "hr") {

    }
    else if(tagName == "a") {

    }
    else if(tagName == "p") {

    }
    else {

    }
}

value* commonTagCloseHandler(tagNode* closeTag) {   // check tag type, return value of tag

    return NULL;
}

value* singleTagHandler(char* tagName, attrNode* attrList) {    // do things for this tag, return value of tag

    return NULL;
}