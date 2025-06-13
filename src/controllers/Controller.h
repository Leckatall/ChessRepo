//
// Created by Lecka on 11/06/2025.
//

#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QObject>

namespace application {
    class Application;  // Forward declaration only
}

class Controller : public QObject {
    Q_OBJECT

public:
    explicit Controller(application::Application *app);
    [[nodiscard]] virtual QWidget *view() const = 0;

public slots:
    virtual void updateData() = 0;

    virtual void updateView() = 0;
};


#endif //CONTROLLER_H
