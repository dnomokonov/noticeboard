#include "listAdverts.h"
#include "viewingad.h"

listAdverts::listAdverts(MainWindow *mainWindow, QWidget *parent)
    : QWidget(parent), mainWindow(mainWindow) {

    QFile styleFile(":/styles/style.css");
    if (styleFile.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        this->setStyleSheet(styleSheet);
    }

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *titleLabel = new QLabel("Список объявлений", this);
    titleLabel->setAlignment(Qt::AlignLeft);
    mainLayout->addWidget(titleLabel);

    scrollArea = new QScrollArea(this);
    scrollArea->setStyleSheet("background: white;");
    scrollContent = new QWidget(scrollArea);
    contentLayout = new QGridLayout(scrollContent);

    scrollContent->setLayout(contentLayout);
    scrollArea->setWidget(scrollContent);
    scrollArea->setWidgetResizable(true);

    mainLayout->addWidget(scrollArea);
    setLayout(mainLayout);

    updateFiltersAndReload();
}

void listAdverts::updateContent(const QString &searchWords, const QStringList &categories, const QString &location) {
    clearLayout(contentLayout);

    int currentUserId = keeper->getUserID();

    QSqlQuery query;
    QString queryString = "SELECT id, title, cost, location, photo FROM Announcements WHERE id_user != :id_user";

    if (!searchWords.isEmpty()) {
        queryString += " AND title LIKE :searchWords";
    }
    if (!categories.isEmpty()) {
        queryString += " AND category IN (" + QStringList(categories).join(",") + ")";
    }
    if (!location.isEmpty()) {
        queryString += " AND location LIKE :location";
    }

    query.prepare(queryString);
    query.bindValue(":id_user", currentUserId);
    if (!searchWords.isEmpty()) {
        query.bindValue(":searchWords", "%" + searchWords + "%");
    }
    if (!location.isEmpty()) {
        query.bindValue(":location", "%" + location + "%");
    }

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

            keeper->setSelectedAnnouncemen(advertId);

            viewingad* viewWidget = qobject_cast<viewingad*>(stackedWidget->widget(5));
            if (viewWidget) {
                viewWidget->loadAdData(advertId);
            }
            stackedWidget->setCurrentIndex(5);
        });
    }

    scrollContent->setLayout(contentLayout);
    scrollArea->setWidget(scrollContent);
    scrollArea->setWidgetResizable(true);
}

void listAdverts::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    // QString emptyString;
    // QStringList emptyCategories;
    // updateContent(emptyString, emptyCategories, emptyString);
}

void listAdverts::setFilters(const QString &searchWords, const QStringList &categories, const QString &location) {
    this->searchWords = searchWords;
    this->categories = categories;
    this->location = location;
}

void listAdverts::updateFiltersAndReload() {
    updateContent(searchWords, categories, location);
}

void listAdverts::clearLayout(QLayout *layout) {
    if (!layout) return;
    while (QLayoutItem *item = layout->takeAt(0)) {
        if (QWidget *widget = item->widget()) {
            delete widget;
        } else if (QLayout *childLayout = item->layout()) {
            clearLayout(childLayout);
        }
        delete item;
    }
}
