#ifndef GLOBAL_H
#define GLOBAL_H
#include <QWidget>
#include<functional>
#include <QRegularExpression>
#include "QStyle"
extern std::function<void(QWidget*)> repolish;// 让qss属性生效需要repolish这个刷新机制

#endif // GLOBAL_H
