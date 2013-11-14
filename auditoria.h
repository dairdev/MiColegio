#ifndef AUDITORIA_H
#define AUDITORIA_H

#include <QDateTime>

class Auditoria
{
public:
    Auditoria();
    void SaveLog(QDateTime realizado_en, int realizado_por, QString accion, QString descripcion);
};

#endif // AUDITORIA_H
