#ifndef KEYPRESS_H
#define KEYPRESS_H


class keyPress
{
public:
    keyPress();

private slots:
    void keyPressEvent(QKeyEvent *e);
};

#endif // KEYPRESS_H
