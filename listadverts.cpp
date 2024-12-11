#include "listadverts.h"

listAdverts::listAdverts(MainWindow *mainWindow, QWidget *parent)
    : QWidget(parent), mainWindow(mainWindow) {

    keeper->loadFromSettings();

    QFile styleFile(":/styles/style.css");
    if (styleFile.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        this->setStyleSheet(styleSheet);
    }

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QLabel *label = new QLabel("Объявления", this);

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setStyleSheet("background: white;");
    QWidget *scrollContent = new QWidget(scrollArea);
    QGridLayout *contentLayout = new QGridLayout(scrollContent);

    int currentUserId = keeper->getUserID();

    QSqlQuery query;
    query.prepare("SELECT id, title, cost, location, photo FROM Announcements WHERE id_user != :id_user");
    query.bindValue(":id_user", currentUserId);

    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
        return;
    }

    int columnCount = 4; // Количество объявлений в строке
    int row = 0;
    int col = 0;

    while (query.next()) {
        int advertId = query.value("id").toInt();
        bool isFavorited = false;
        QString title = query.value("title").toString();
        double cost = query.value("cost").toDouble();
        QString location = query.value("location").toString().split(",").first();
        QByteArray photoData = query.value("photo").toByteArray();

        QSqlQuery checkFavoriteQuery;
        checkFavoriteQuery.prepare("SELECT COUNT(*) FROM Favorites WHERE id_user = :id_user AND id_announcement = :id_announcement");
        checkFavoriteQuery.bindValue(":id_user", currentUserId);
        checkFavoriteQuery.bindValue(":id_announcement", advertId);

        if (checkFavoriteQuery.exec() && checkFavoriteQuery.next()) {
            isFavorited = (checkFavoriteQuery.value(0).toInt() > 0);
        }

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

        QHBoxLayout *titleLayout = new QHBoxLayout();
        titleLayout->setContentsMargins(0, 0, 0, 0);
        titleLayout->setSpacing(5);

        QLabel *titleLabel = new QLabel(QString("%1").arg(title), advertCard);
        titleLabel->setObjectName("titleCard");
        titleLayout->addWidget(titleLabel);

        titleLayout->addStretch();

        QPushButton *favoriteButton = new QPushButton(advertCard);
        favoriteButton->setObjectName("onlyIconButton");

        QPixmap iconFavFull(":/icons/fav_full");
        QIcon favFullIcon(iconFavFull);
        QPixmap iconFav(":/icons/fav_empty");
        QIcon favButtonIcon(iconFav);

        if (isFavorited) {
            favoriteButton->setIcon(favFullIcon);
        } else {
            favoriteButton->setIcon(favButtonIcon);
        }

        favoriteButton->setIconSize(QSize(24, 22));
        favoriteButton->setFixedSize(30, 30);
        favoriteButton->setStyleSheet("background: none; border: none;");
        titleLayout->addWidget(favoriteButton);

        cardLayout->addLayout(titleLayout);

        QLabel *costLabel = new QLabel(QString("%1 руб.").arg(cost), advertCard);
        costLabel->setObjectName("costCard");
        cardLayout->addWidget(costLabel);

        QLabel *locationLabel = new QLabel(QString("%1").arg(location), advertCard);
        locationLabel->setObjectName("locationCard");
        cardLayout->addWidget(locationLabel);

        QHBoxLayout *buttonLayout = new QHBoxLayout();
        buttonLayout->setSpacing(5);

        QPushButton *viewButton = new QPushButton("Посмотреть", advertCard);
        viewButton->setObjectName("cardButton");

        buttonLayout->addStretch();
        buttonLayout->addWidget(viewButton);

        cardLayout->addLayout(buttonLayout);
        advertCard->setLayout(cardLayout);

        contentLayout->addWidget(advertCard, row, col);

        col++;
        if (col >= columnCount) {
            col = 0;
            row++;
        }

        advertCard->setProperty("isFavorited", isFavorited);

        connect(favoriteButton, &QPushButton::clicked, this, [=,  &isFavorited]() mutable  {
            if (currentUserId == 0) {
                QMessageBox::warning(this, "Внимание", "Чтобы добавить в избранное, войдите в аккаунт.");
                return;
            }

            bool isFavorited = advertCard->property("isFavorited").toBool();

            QSqlQuery favoriteQuery;
            if (isFavorited) {
                favoriteQuery.prepare("DELETE FROM Favorites WHERE id_user = :id_user AND id_announcement = :id_announcement");
                favoriteQuery.bindValue(":id_user", currentUserId);
                favoriteQuery.bindValue(":id_announcement", advertId);

                if (!favoriteQuery.exec()) {
                    qDebug() << "Ошибка удаления из избранного:" << favoriteQuery.lastError().text();
                } else {
                    favoriteButton->setIcon(favButtonIcon);
                    advertCard->setProperty("isFavorited", false);
                }
            } else {
                favoriteQuery.prepare("INSERT INTO Favorites (id_user, id_announcement) VALUES (:id_user, :id_announcement)");
                favoriteQuery.bindValue(":id_user", currentUserId);
                favoriteQuery.bindValue(":id_announcement", advertId);

                if (!favoriteQuery.exec()) {
                    qDebug() << "Ошибка добавления в избранное:" << favoriteQuery.lastError().text();
                } else {
                    favoriteButton->setIcon(favFullIcon);
                    advertCard->setProperty("isFavorited", true);
                }
            }
        });

        connect(viewButton, &QPushButton::clicked, this, [=]() {


            QStackedWidget* stackedWidget = mainWindow->getStackedWidget();
            stackedWidget->setCurrentIndex(6);
        });
    }

    scrollContent->setLayout(contentLayout);
    scrollArea->setWidget(scrollContent);
    scrollArea->setWidgetResizable(true);

    mainLayout->addWidget(label);
    mainLayout->addWidget(scrollArea);
    setLayout(mainLayout);
}
