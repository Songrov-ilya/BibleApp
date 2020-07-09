#include "Content.h"


void Content::generateOnlineContent()
{
    static Server server;
    server.getOnlineBookList();
}

void Content::generateContentStandart(const Content::Standard standart)
{
    //    generateContent_Photos();
    generateContent_Folders();
    generateContent_Info(standart);
    generateContent_JsonText(standart);
    generateContent_TwoArraysBooks();
}

void Content::generateContent_Folders()
{
    QDir().mkdir(Path::dirContent_Old_Testament_Photos);
    QDir().mkdir(Path::dirContent_New_Testament_Photos);
    QDir().mkdir(Path::dirContent_Old_Testament_JsonText);
    QDir().mkdir(Path::dirContent_New_Testament_JsonText);
}

void Content::generateContent_Photos()
{
    const int Old_New_Testament { 2 };
    for (int var = 0; var < Old_New_Testament; ++var) {
        const QString dirContent = var == 0 ? Path::dirContent_Old_Testament_Photos : Path::dirContent_New_Testament_Photos;
        const QString fileContent = var == 0 ? Path::fileContent_Old_Testament_Photos : Path::fileContent_New_Testament_Photos;

        QJsonObject objMain;
        QStringList listDir = getListFileInDirectory(QFileInfo(dirContent).absolutePath());
        for (int var = 0; var < listDir.size(); ++var) {
            const QString bookIndex = getIndexBookStr(var);
            QJsonObject objBook;
            fillPhotos(&objBook, dirContent + bookIndex);
            objMain.insert(bookIndex, objBook);
        }
        FileWorker::writeFileJson(QJsonDocument(objMain), fileContent);
    }


    //    {
    //        "book_36": {
    //            "IMG_20190604_124816_HDR.jpg": "0",
    //            "IMG_20190604_124821_HDR.jpg": "0"
    //        },
    //        "book_37": {
    //            "IMG_20190604_124821_HDR.jpg": "0",
    //            "IMG_20190604_124827_HDR.jpg": "0"
    //        },
    //        "book_38": {
    //            "IMG_20190604_124827_HDR.jpg": "0",
    //            "IMG_20190604_124835_HDR.jpg": "0",
    //            "IMG_20190604_124841_HDR.jpg": "0",
    //            "IMG_20190604_124848_HDR.jpg": "0",
    //            "IMG_20190604_124854_HDR.jpg": "0",
    //            "IMG_20190604_124901_HDR.jpg": "0"
    //        },
    //    }
}

void Content::generateNewNameFolder_Photos()
{
    const int Old_New_Testament { 2 };
    for (int var = 0; var < Old_New_Testament; ++var) {
        const QString dirContent = var == 0 ? Path::dirContent_Old_Testament_Photos : Path::dirContent_New_Testament_Photos;
        const QString fileContent = var == 0 ? Path::fileContent_Old_Testament_Photos : Path::fileContent_New_Testament_Photos;

        QStringList listDir = getListFileInDirectory(QFileInfo(dirContent).absolutePath());
        for (int var = 0; var < listDir.size(); ++var) {
            const QString bookIndex = getIndexBookStr(var);
            QFile::rename(dirContent + getIndexBookStr(var), dirContent + bookIndex);
        }
    }
}

void Content::generateContent_Info(const Content::Standard standart)
{
    QJsonDocument doc;
    // Path::allBibleJsonText has the Standard::Western standart.
    FileWorker::readFileJson(&doc, Path::allBibleJsonText);
    QJsonArray arrMain = doc.array();

    QJsonObject objOldTestament;
    QJsonObject objNewTestament;
    for (int var = 0; var < arrMain.size(); ++var) {
        QJsonObject objBook = arrMain.at(var).toObject();
        objBook.remove("chapters");
        objBook.insert("name_en", objBook.value("name").toString());
        objBook.remove("name");

        QVector<QString> vecFamilyBooks;
        QString family_books_en;
        QString family_books_ru;
        QString bookIndex;
        int nextFamily { 0 };
        QJsonObject *refObjTestament = &objOldTestament;
        if (var < BibleEnums::Old_Testament) {
            if (var < FamilyBooks::Pentateuch) {
                vecFamilyBooks = { "Бытие", "Исход", "Левит", "Числа", "Второзаконие" };
                family_books_en = "Pentateuch";
                family_books_ru = "Пятикнижие";
            }
            else if (var < FamilyBooks::HistoricalBooks) {
                vecFamilyBooks = { "Иисус Навин", "Судьи", "Руфь", "1 Царств", "2 Царств", "3 Царств", "4 Царств",
                                   "1 Паралипомен", "2 Паралипомен", "Ездра", "Неемия", "Есфирь" };
                family_books_en = "Historical Books";
                family_books_ru = "Исторические";
                nextFamily = FamilyBooks::Pentateuch;
            }
            else if (var < FamilyBooks::Wisdom) {
                vecFamilyBooks = { "Иов", "Псалтирь", "Притчи", "Екклеcиаст", "Песня песней" };
                family_books_en = "Wisdom";
                family_books_ru = "Учительные";
                nextFamily = FamilyBooks::HistoricalBooks;
            }
            else if (var < FamilyBooks::MajorProphets) {
                vecFamilyBooks = { "Исаия", "Иеремия", "Плач Иеремии", "Иезекииль", "Даниил" };
                family_books_en = "Major Prophets";
                family_books_ru = "Большие пророки";
                nextFamily = FamilyBooks::Wisdom;
            }
            else if (var < FamilyBooks::MinorProphets) {
                vecFamilyBooks = { "Осия", "Иоиль", "Амос", "Авдий", "Иона", "Михей", "Наум", "Аввакум", "Софония", "Аггей",
                                   "Захария", "Малахия" };
                family_books_en = "Minor Prophets";
                family_books_ru = "Малые пророки";
                nextFamily = FamilyBooks::MajorProphets;
            }
            bookIndex = getIndexBookStr(var);
        }
        else{
            if (var < FamilyBooks::GospelsAndActs) {
                vecFamilyBooks = { "Матфея", "Марка", "Луки", "Иоанна", "Деяния" };
                family_books_en = "Gospels and Acts";
                family_books_ru = "Евангелия и Деяния";
                nextFamily = FamilyBooks::MinorProphets;
            }
            else if (var < FamilyBooks::PaulineEpistles) {
                vecFamilyBooks = { "Римлянам", "1 Коринфянам", "2 Коринфянам", "Галатам", "Ефесянам", "Филиппийцам", "Колоссянам",
                                   "1 Фессалоникийцам", "2 Фессалоникийцам", "1 Тимофею", "2 Тимофею", "Титу", "Филимону", "Евреям"};
                family_books_en = "Pauline Epistles";
                family_books_ru = "Послания Павла";
                nextFamily = FamilyBooks::GospelsAndActs;
            }
            else if (var < FamilyBooks::CatholicEpistles) {
                vecFamilyBooks = { "Иакова", "1 Петра", "2 Петра", "1 Иоанна", "2 Иоанна", "3 Иоанна", "Иуда" };
                family_books_en = "Catholic Epistles";
                family_books_ru = "Соборные послания";
                nextFamily = FamilyBooks::PaulineEpistles;
            }
            else if (var < FamilyBooks::Apocalypse) {
                vecFamilyBooks = { "Откровение" };
                family_books_en = "Apocalypse";
                family_books_ru = "Пророческие";
                nextFamily = FamilyBooks::CatholicEpistles;
            }
            bookIndex = getIndexBookStr(var, BibleEnums::New_Testament, standart);
            refObjTestament = &objNewTestament;
        }
        objBook.insert("name_ru", vecFamilyBooks.at(var - nextFamily));
        objBook.insert("family_books_en", family_books_en);
        objBook.insert("family_books_ru", family_books_ru);

        refObjTestament->insert(bookIndex, objBook);
    }
    FileWorker::writeFileJson(QJsonDocument(objOldTestament), Path::fileContent_Old_Testament_Info);
    FileWorker::writeFileJson(QJsonDocument(objNewTestament), Path::fileContent_New_Testament_Info);

    //    [
    //        {
    //        "abbrev" : "abbrev"
    //        "name" : "book"
    //        "chapters":
    //            [
    //                ["Verse 1", "Verse 2", "Verse 3", "..."],
    //                ["Verse 1", "Verse 2", "Verse 3", "..."],
    //                ["Verse 1", "Verse 2", "Verse 3", "..."]
    //            ]
    //        },
    //        {
    //        ...
    //        },
    //    ]
}

void Content::generateContent_JsonText(const Standard standart)
{
    QJsonDocument doc;
    // Path::allBibleJsonText has the Standard::Western standart.
    FileWorker::readFileJson(&doc, Path::allBibleJsonText);
    QJsonArray arrMain = doc.array();

    QString dirContent { Path::dirContent_Old_Testament_JsonText };
    for (int var = 0; var < arrMain.size(); ++var) {
        QJsonObject objBook = arrMain.at(var).toObject();
        QJsonArray arrChapters = objBook.value("chapters").toArray();
        if (var < BibleEnums::Old_Testament) {
            const QString bookIndex = getIndexBookStr(var);
            FileWorker::writeFileJson(QJsonDocument(arrChapters), dirContent + bookIndex + ".json");
        }
        else{
            dirContent = Path::dirContent_New_Testament_JsonText;
            const QString bookIndex = getIndexBookStr(var, BibleEnums::New_Testament, standart);
            FileWorker::writeFileJson(QJsonDocument(arrChapters), dirContent + bookIndex + ".json");
        }
    }

    //    [
    //        {
    //        "abbrev" : "abbrev"
    //        "name" : "book"
    //        "chapters":
    //            [
    //                ["Verse 1", "Verse 2", "Verse 3", "..."],
    //                ["Verse 1", "Verse 2", "Verse 3", "..."],
    //                ["Verse 1", "Verse 2", "Verse 3", "..."]
    //            ]
    //        },
    //        {
    //        ...
    //        },
    //    ]
}

void Content::generateContent_TwoArraysBooks()
{
    const int Old_New_Testament { 2 };
    for (int var = 0; var < Old_New_Testament; ++var) {
        const QString fileContentJsonText = var == 0 ? Path::fileContent_Old_Testament_Info: Path::fileContent_New_Testament_Info;
        const QString fileContentArrayBooks = var == 0 ? Path::fileContent_Old_Testament_ArrayBooks : Path::fileContent_New_Testament_ArrayBooks;

        QJsonDocument doc;
        QJsonArray arrBooks;
        FileWorker::readFileJson(&doc, fileContentJsonText);
        QJsonObject objMain = doc.object();
        QStringList listKeys { objMain.keys() };
        for (const QString &bookKey : listKeys) {
            QJsonObject objBook = objMain.value(bookKey).toObject();
            arrBooks.append(objBook.value("name_ru"));
        }
        FileWorker::writeFileJson(QJsonDocument(arrBooks), fileContentArrayBooks);
    }
}

void Content::loadContent_Photos(QVector<Book> *vecBooks, const BibleEnums::Testament testament)
{
    const QString dirContent = testament == BibleEnums::Old_Testament ? Path::dirContent_Old_Testament_Photos : Path::dirContent_New_Testament_Photos;
    const QString fileContent = testament == BibleEnums::Old_Testament ? Path::fileContent_Old_Testament_Photos : Path::fileContent_New_Testament_Photos;
    QJsonDocument doc;
    FileWorker::readFileJson(&doc, fileContent);

    QJsonObject obj = doc.object();
    QStringList listKeys = obj.keys();
    Q_ASSERT(listKeys.isEmpty() != vecBooks->size());

    for (int var = 0; var < testament; ++var) {
        (*vecBooks)[var].loadContentPhotos(obj.value(listKeys.at(var)).toObject(), dirContent);
    }
}

void Content::loadContenet_ArrayBooks(QStringList *list, const BibleEnums::Testament testament)
{
    const QString nameFile = testament == BibleEnums::Old_Testament ? Path::fileContent_Old_Testament_ArrayBooks : Path::fileContent_New_Testament_ArrayBooks;
    QJsonDocument doc;
    FileWorker::readFileJson(&doc, nameFile);
    QJsonArray arr = doc.array();
    std::for_each(arr.begin(), arr.end(), [list](const QJsonValue &value){ list->append(value.toString()); });
}

void Content::loadContenet_OneBook(Book *book, const BibleEnums::Testament testament)
{
    Q_ASSERT(book);
    const QString dirContent = testament == BibleEnums::Old_Testament ? Path::dirContent_Old_Testament_JsonText : Path::dirContent_New_Testament_JsonText;
    const QString pathBook = dirContent + getIndexBookStr(book->getIndexBook()) + ".json";
    QJsonDocument doc;
    FileWorker::readFileJson(&doc, pathBook);
    book->loadContentChapterText(doc.array());
}

void Content::loadTextVersesJson(QVector<Book> *vecBooks, const BibleEnums::Testament testament)
{
    const QString fileContent = testament == BibleEnums::Old_Testament ? Path::fileContent_Old_Testament_Info : Path::fileContent_New_Testament_Info;
    QJsonDocument doc;
    FileWorker::readFileJson(&doc, fileContent);


    //    Helper::readFileJson(&doc, Path::allBibleJsonText);
    //    QJsonArray arrBooks = doc.array();

    //    for (const QJsonValue &book: arrBooks) {
    //        QJsonObject objBook = book.toObject();
    //        QString bookName = objBook.value("name").toString();
    //        for (Book &book: *vecBooks) {
    //            if(book.getNameEn() == bookName){
    //                QJsonArray arrChapters = objBook.value("chapters").toArray();
    //                for(const QJsonValue &chapter : arrChapters){
    //                    book.appentChapter(Chapter(chapter.toArray()));
    //                }
    //                break;
    //            }
    //        }
    //    }
}


QStringList Content::getListFileInDirectory(const QString &dir)
{
    QStringList list;
    const QDir directory(dir);

    for(const QFileInfo &info: directory.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot)) {
        //        if(!info.isDir()){
        list.append(info.absoluteFilePath());
        //        }
    }
    list.sort();
    return list;
}

void Content::fillPhotos(QJsonObject *objBook, const QString &pathDir)
{
    QStringList list = getListFileInDirectory(pathDir);
    for (const QString &str: list) {
        objBook->insert(QFileInfo(str).fileName(), "0");
    }
}

QString Content::getIndexBookStr(const int indexBook)
{
    return "book_" + QString::number(indexBook).rightJustified(2, '0');
}

QString Content::getIndexBookStr(int indexBook, const BibleEnums::Testament testament, const Content::Standard standart)
{
    if (standart == Standard::EasternSynodal) {
        const int quantityCatholicEpistles { 7 };
        const int quantityPaulineEpistles { 14 };
        if (indexBook >= FamilyBooks::GospelsAndActs && indexBook < FamilyBooks::GospelsAndActs + quantityPaulineEpistles) {
            indexBook += quantityCatholicEpistles;
        }
        else if(indexBook >= FamilyBooks::PaulineEpistles && indexBook < FamilyBooks::PaulineEpistles + quantityCatholicEpistles) {
            indexBook -= quantityPaulineEpistles;
        }
    }
    if (testament == BibleEnums::New_Testament) {
        indexBook -= BibleEnums::Old_Testament;
    }
    return getIndexBookStr(indexBook);
}

