#include "global.h"

std::function<void(QWidget*)> repolish = [](QWidget* w){
    w->style()->unpolish(w); // 将原来的样式去了
    w->style()->polish(w);   // 将样式刷新就成了新的样式了
};
