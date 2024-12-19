#include "shoppingcart.h"
#include "viewingad.h"
#include "editannouncement.h"

shoppingcart::shoppingcart(MainWindow *mainWindow, QWidget *parent)
    : mainWindow(mainWindow), QWidget(parent) {

    keeper = mainWindow->getKeeperData();

    if (!keeper) {
        qDebug() << "KeeperData is null!";
    }

    QFile styleFile(":/styles/style.css");
    if (styleFile.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        this->setStyleSheet(styleSheet);
    }

    keeper->loadFromSettings();

    mainLayout = new QVBoxLayout(this);

    label = new QLabel("Мои объявления", this);
    label->setObjectName("myAdsLabel");
    mainLayout->addWidget(label);

    scrollArea = new QScrollArea(this);
    scrollArea->setStyleSheet("background: white; border:none;");
    scrollContent = new QWidget(scrollArea);
    contentLayout = new QGridLayout(scrollContent);
    contentLayout->setSpacing(10);
    contentLayout->setContentsMargins(10, 10, 10, 10);

    scrollContent->setLayout(contentLayout);
    scrollArea->setWidget(scrollContent);
    scrollArea->setWidgetResizable(true);

    mainLayout->addWidget(scrollArea);
    setLayout(mainLayout);

    updateContent();
}

void shoppingcart::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    updateContent();
}

void shoppingcart::updateContent()
{
    QLayoutItem *child;
    while ((child = contentLayout->takeAt(0)) != nullptr) {
        if (child->widget()) {
            child->widget()->deleteLater();
        }
        delete child;
    }

    int currentUserId = keeper->getUserID();

    QSqlQuery query;
    query.prepare(R"(
        SELECT id, title, cost, location, photo
        FROM Announcements
        WHERE id_user = :id_user
    )");
    query.bindValue(":id_user", currentUserId);

    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
        return;
    }

    int columnCount = 4;
    int row = 0;
    int col = 0;

    while (query.next()) {
        int advertId = query.value("id").toInt();
        QString title = query.value("title").toString();
        double cost = query.value("cost").toDouble();
        QString location = query.value("location").toString().split(",").first();
        QByteArray photoData = query.value("photo").toByteArray();

        QWidget *advertCard = new QWidget(scrollContent);
        advertCard->setFixedSize(240, 320);
        advertCard->setStyleSheet("background: #F3F3F3;");
        advertCard->setObjectName("CardWidget");

        QVBoxLayout *cardLayout = new QVBoxLayout(advertCard);
        cardLayout->setSpacing(5);
        cardLayout->setContentsMargins(5, 10, 5, 5);

        QHBoxLayout *imageLayout = new QHBoxLayout();
        imageLayout->setContentsMargins(0, 0, 0, 0);

        QLabel *photoLabel = new QLabel(advertCard);
        photoLabel->setAlignment(Qt::AlignCenter);
        QPixmap pixmap;
        if (pixmap.loadFromData(photoData)) {
            photoLabel->setPixmap(pixmap.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else {
            photoLabel->setText("Нет изображения");
            photoLabel->setAlignment(Qt::AlignCenter);
        }
        imageLayout->addWidget(photoLabel);

        cardLayout->addLayout(imageLayout);

        QLabel *titleLabel = new QLabel(title, advertCard);
        titleLabel->setObjectName("titleCard");
        cardLayout->addWidget(titleLabel);

        QLabel *costLabel = new QLabel(QString("%1 руб.").arg(cost), advertCard);
        costLabel->setObjectName("costCard");
        cardLayout->addWidget(costLabel);

        QLabel *locationLabel = new QLabel(location, advertCard);
        locationLabel->setObjectName("locationCard");
        cardLayout->addWidget(locationLabel);

        QHBoxLayout *buttonLayout = new QHBoxLayout();

        QPushButton *ebitButton = new QPushButton("Редактировать", advertCard);
        ebitButton->setObjectName("cardButton");

        QPushButton *viewButton = new QPushButton("Посмотреть", advertCard);
        viewButton->setObjectName("cardButton");

        buttonLayout->addStretch();
        buttonLayout->addWidget(ebitButton);
        buttonLayout->addWidget(viewButton);

        cardLayout->addLayout(buttonLayout);
        advertCard->setLayout(cardLayout);

        contentLayout->addWidget(advertCard, row, col);

        col++;
        if (col >= columnCount) {
            col = 0;
            row++;
        }

        connect(ebitButton, &QPushButton::clicked, this, [=]() {
            QStackedWidget* stackedWidget = mainWindow->getStackedWidget();

            EditAnnouncement* editPage = qobject_cast<EditAnnouncement*>(stackedWidget->widget(6));

            editPage->setIDAnnouncement(advertId);

            stackedWidget->setCurrentIndex(6);
        });

        connect(viewButton, &QPushButton::clicked, this, [=]() {
            QStackedWidget* stackedWidget = mainWindow->getStackedWidget();

            keeper->setSelectedAnnouncemen(advertId);

            viewingad* viewWidget = qobject_cast<viewingad*>(stackedWidget->widget(5));
            if (viewWidget) {
                viewWidget->loadAdData(advertId);
            }
            stackedWidget->setCurrentIndex(5);
        });
    }
}
