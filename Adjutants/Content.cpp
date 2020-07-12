#include "Content.h"

#ifdef QT_DEBUG
QNetworkAccessManager Content::mngr;

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

void Content::generateContent_Folders(const Content::TypeContent typeContent)
{
    QDir().mkdir(Path::dirContent_Old_Testament_Photos);
    QDir().mkdir(Path::dirContent_New_Testament_Photos);
    QString dirContent_Old { Path::dirContent_Old_Testament_JsonText_BODRUK };
    QString dirContent_New { Path::dirContent_New_Testament_JsonText_BODRUK };
    if (typeContent == GITHUB_BIBLE_USFM2JSON_RUSLAN_KAZAKOV) {
        dirContent_Old = Path::dirContent_Old_Testament_JsonText_KAZAKOV;
        dirContent_New = Path::dirContent_New_Testament_JsonText_KAZAKOV;
    }
    QDir(dirContent_Old).removeRecursively();
    QDir(dirContent_New).removeRecursively();
    QThread::msleep(2000);
    QDir().mkdir(dirContent_Old);
    QDir().mkdir(dirContent_New);
}

void Content::generateContentStandart(const Content::Standard requiredStandart, const TypeContent typeContent)
{
    generateContent_Folders(typeContent);
    if (typeContent == GITHUB_BIBLE_XML_AND_JSON_THIAGO_BODRUK) {
        generateContent_Info_BODRUK(requiredStandart);
        generateContent_JsonText_BODRUK(requiredStandart);
    }
    if(typeContent == BIBLEONLINE_RU){
        //        getOnlineBookList();
        //        generateContent_Info_ONLINE(standart);
        //        getOnlineBible();
        //        generateContent_JsonText_ONLINE(standart);
    }
    if(typeContent == GITHUB_BIBLE_USFM2JSON_RUSLAN_KAZAKOV){
        generateValidJson_KAZAKOV();
        generateContent_Info_KAZAKOV(requiredStandart);
        generateContent_JsonText_KAZAKOV(requiredStandart);
    }
    generateContent_TwoArraysBooks(typeContent);
}

void Content::generateContent_Info_BODRUK(const Content::Standard requiredStandart)
{
    QJsonDocument doc;
    // Path::allBibleJsonText has the Standard::Western standart.
    FileWorker::readFileJson(&doc, Path::allBibleJsonText_BODRUK);
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
                vecFamilyBooks = getVectorFamilyBooks(Pentateuch);
                family_books_en = getNameFamilyBooks(Pentateuch, "en");
                family_books_ru = getNameFamilyBooks(Pentateuch, "ru");
            }
            else if (var < FamilyBooks::HistoricalBooks) {
                vecFamilyBooks = getVectorFamilyBooks(HistoricalBooks);
                family_books_en = getNameFamilyBooks(HistoricalBooks, "en");
                family_books_ru = getNameFamilyBooks(HistoricalBooks, "ru");
                nextFamily = FamilyBooks::Pentateuch;
            }
            else if (var < FamilyBooks::Wisdom) {
                vecFamilyBooks = getVectorFamilyBooks(Wisdom);
                family_books_en = getNameFamilyBooks(Wisdom, "en");
                family_books_ru = getNameFamilyBooks(Wisdom, "ru");
                nextFamily = FamilyBooks::HistoricalBooks;
            }
            else if (var < FamilyBooks::MajorProphets) {
                vecFamilyBooks = getVectorFamilyBooks(MajorProphets);
                family_books_en = getNameFamilyBooks(MajorProphets, "en");
                family_books_ru = getNameFamilyBooks(MajorProphets, "ru");
                nextFamily = FamilyBooks::Wisdom;
            }
            else if (var < FamilyBooks::MinorProphets) {
                vecFamilyBooks = getVectorFamilyBooks(MinorProphets);
                family_books_en = getNameFamilyBooks(MinorProphets, "en");
                family_books_ru = getNameFamilyBooks(MinorProphets, "ru");
                nextFamily = FamilyBooks::MajorProphets;
            }
            bookIndex = getIndexBookStr(var);
        }
        else{
            if (var < FamilyBooks::GospelsAndActs) {
                vecFamilyBooks = getVectorFamilyBooks(GospelsAndActs);
                family_books_en = getNameFamilyBooks(GospelsAndActs, "en");
                family_books_ru = getNameFamilyBooks(GospelsAndActs, "ru");
                nextFamily = FamilyBooks::MinorProphets;
            }
            else if (var < FamilyBooks::PaulineEpistles) {
                vecFamilyBooks = getVectorFamilyBooks(PaulineEpistles);
                family_books_en = getNameFamilyBooks(PaulineEpistles, "en");
                family_books_ru = getNameFamilyBooks(PaulineEpistles, "ru");
                nextFamily = FamilyBooks::GospelsAndActs;
            }
            else if (var < FamilyBooks::CatholicEpistles) {
                vecFamilyBooks = getVectorFamilyBooks(CatholicEpistles);
                family_books_en = getNameFamilyBooks(CatholicEpistles, "en");
                family_books_ru = getNameFamilyBooks(CatholicEpistles, "ru");
                nextFamily = FamilyBooks::PaulineEpistles;
            }
            else if (var < FamilyBooks::Apocalypse) {
                vecFamilyBooks = getVectorFamilyBooks(Apocalypse);
                family_books_en = getNameFamilyBooks(Apocalypse, "en");
                family_books_ru = getNameFamilyBooks(Apocalypse, "ru");
                nextFamily = FamilyBooks::CatholicEpistles;
            }
            bookIndex = getIndexBookStr(var, BibleEnums::New_Testament, Standard::Western, requiredStandart);
            refObjTestament = &objNewTestament;
        }
        objBook.insert("name_ru", vecFamilyBooks.at(var - nextFamily));
        objBook.insert("family_books_en", family_books_en);
        objBook.insert("family_books_ru", family_books_ru);

        refObjTestament->insert(bookIndex, objBook);
    }
    FileWorker::writeFileJson(QJsonDocument(objOldTestament), Path::fileContent_Old_Testament_Info_BODRUK);
    FileWorker::writeFileJson(QJsonDocument(objNewTestament), Path::fileContent_New_Testament_Info_BODRUK);

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

void Content::generateContent_Info_ONLINE(const Content::Standard requiredStandart)
{
    QJsonDocument doc;
    FileWorker::readFileJson(&doc, Path::tempJson);
    QJsonArray arrMain = doc.array();

    QJsonObject objOldTestament;
    QJsonObject objNewTestament;
    QString family_books_en;
    QString family_books_ru;
    for (int var = 0; var < arrMain.size(); ++var) {
        QJsonObject obj = arrMain.at(var).toObject();
        if (obj.keys().contains("h4")) {
            family_books_en = getNameFamilyBooks(FamilyBooks::Wisdom, "en");
            family_books_ru = obj.value("h4").toString();
        }
        if (!obj.keys().contains("li")) {
            continue;
        }
        QJsonObject objBook = obj.value("li").toObject();
        objBook.insert("name_en", objBook.value("Name").toString());
        objBook.remove("Name");
        objBook.insert("name_ru", objBook.value("locale").toString());
        objBook.remove("locale");
        int index = objBook.value("id").toString().toInt() - 1;
        objBook.remove("id");

        QString bookIndex;
        QJsonObject *refObjTestament = &objOldTestament;
        if (index < BibleEnums::Old_Testament) {
            if (index < FamilyBooks::Pentateuch) {
                family_books_en = getNameFamilyBooks(Pentateuch, "en");
            }
            else if (index < FamilyBooks::HistoricalBooks) {
                family_books_en = getNameFamilyBooks(HistoricalBooks, "en");
            }
            else if (index < FamilyBooks::Wisdom) {
                family_books_en = getNameFamilyBooks(Wisdom, "en");
            }
            else if (index < FamilyBooks::MajorProphets) {
                family_books_en = getNameFamilyBooks(MajorProphets, "en");
            }
            else if (index < FamilyBooks::MinorProphets) {
                family_books_en = getNameFamilyBooks(MinorProphets, "en");
            }
            bookIndex = getIndexBookStr(index);
        }
        else{
            if (index < FamilyBooks::GospelsAndActs) {
                family_books_en = getNameFamilyBooks(GospelsAndActs, "en");
            }
            else if (index < FamilyBooks::PaulineEpistles) {
                family_books_en = getNameFamilyBooks(PaulineEpistles, "en");
            }
            else if (index < FamilyBooks::CatholicEpistles) {
                family_books_en = getNameFamilyBooks(CatholicEpistles, "en");
            }
            else if (index < FamilyBooks::Apocalypse) {
                family_books_en = getNameFamilyBooks(Apocalypse, "en");
            }
            bookIndex = getIndexBookStr(index, BibleEnums::New_Testament, Standard::Western, requiredStandart);
            refObjTestament = &objNewTestament;
        }
        objBook.insert("family_books_en", family_books_en);
        objBook.insert("family_books_ru", family_books_ru);

        refObjTestament->insert(bookIndex, objBook);
    }
    FileWorker::writeFileJson(QJsonDocument(objOldTestament), Path::fileContent_Old_Testament_Info_ONLINE);
    FileWorker::writeFileJson(QJsonDocument(objNewTestament), Path::fileContent_New_Testament_Info_ONLINE);

    //    [
    //        {
    //            "h2": "Русский синодальный перевод"
    //        },
    //        {
    //            "h3": "Книги Ветхого завета"
    //        },
    //        {
    //            "h4": "Пятикнижие Моисея"
    //        },
    //        {
    //            "li": {
    //                "Name": "Genesis",
    //                "id": "1",
    //                "locale": "Книга Бытие"
    //            }
    //        },
    //        {
    //            "li": {
    //                "Name": "Exodus",
    //                "id": "2",
    //                "locale": "Книга Исход"
    //            }
    //        },
    //        {
    //            "li": {
    //                "Name": "Leviticus",
    //                "id": "3",
    //                "locale": "Книга Левит"
    //            }
    //        },
    //        {
    //            "li": {
    //                "Name": "Numbers",
    //                "id": "4",
    //                "locale": "Книга Числа"
    //            }
    //        },
    //        {
    //            "li": {
    //                "Name": "Deuteronomy",
    //                "id": "5",
    //                "locale": "Книга Второзаконие"
    //            }
    //        },
    //        {
    //            "h4": "Книги исторические"
    //        },
    //        {
    //            "li": {
    //                "Name": "Joshua",
    //                "id": "6",
    //                "locale": "Книга Иисуса Навина"
    //            }
    //        },
    //        ...
    //    ]
}

void Content::generateContent_Info_KAZAKOV(const Content::Standard requiredStandart)
{
    QJsonDocument doc;
    // Path::allBibleJsonText has the Standard::Western standart.
    FileWorker::readFileJson(&doc, Path::tempJson);
    QJsonArray arrMain = doc.array();

    Q_ASSERT(!arrMain.isEmpty());

    QJsonObject objOldTestament;
    QJsonObject objNewTestament;
    int index = -1;
    for (int var = 0; var < arrMain.size(); ++var) {
        QJsonObject objBook = arrMain.at(var).toObject();
        if (objBook.value("chapter").toInt() != 1 || objBook.value("verse").toInt() != 1) {
            continue;
        }
        ++index;
        objBook.remove("chapter");
        objBook.remove("verse");
        objBook.remove("text");
        objBook.insert("name_en", objBook.value("book_name").toString());
        objBook.remove("book_name");

        QVector<QString> vecFamilyBooks;
        QString family_books_en;
        QString family_books_ru;
        QString bookIndex;
        int nextFamily { 0 };
        QJsonObject *refObjTestament = &objOldTestament;
        if (index < BibleEnums::Old_Testament) {
            if (index < FamilyBooks::Pentateuch) {
                vecFamilyBooks = getVectorFamilyBooks(Pentateuch);
                family_books_en = getNameFamilyBooks(Pentateuch, "en");
                family_books_ru = getNameFamilyBooks(Pentateuch, "ru");
            }
            else if (index < FamilyBooks::HistoricalBooks) {
                vecFamilyBooks = getVectorFamilyBooks(HistoricalBooks);
                family_books_en = getNameFamilyBooks(HistoricalBooks, "en");
                family_books_ru = getNameFamilyBooks(HistoricalBooks, "ru");
                nextFamily = FamilyBooks::Pentateuch;
            }
            else if (index < FamilyBooks::Wisdom) {
                vecFamilyBooks = getVectorFamilyBooks(Wisdom);
                family_books_en = getNameFamilyBooks(Wisdom, "en");
                family_books_ru = getNameFamilyBooks(Wisdom, "ru");
                nextFamily = FamilyBooks::HistoricalBooks;
            }
            else if (index < FamilyBooks::MajorProphets) {
                vecFamilyBooks = getVectorFamilyBooks(MajorProphets);
                family_books_en = getNameFamilyBooks(MajorProphets, "en");
                family_books_ru = getNameFamilyBooks(MajorProphets, "ru");
                nextFamily = FamilyBooks::Wisdom;
            }
            else if (index < FamilyBooks::MinorProphets) {
                vecFamilyBooks = getVectorFamilyBooks(MinorProphets);
                family_books_en = getNameFamilyBooks(MinorProphets, "en");
                family_books_ru = getNameFamilyBooks(MinorProphets, "ru");
                nextFamily = FamilyBooks::MajorProphets;
            }
            bookIndex = getIndexBookStr(index);
        }
        else{
            if (index < FamilyBooks::GospelsAndActs) {
                vecFamilyBooks = getVectorFamilyBooks(GospelsAndActs);
                family_books_en = getNameFamilyBooks(GospelsAndActs, "en");
                family_books_ru = getNameFamilyBooks(GospelsAndActs, "ru");
                nextFamily = FamilyBooks::MinorProphets;
            }
            else if (index < FamilyBooks::PaulineEpistles) {
                vecFamilyBooks = getVectorFamilyBooks(PaulineEpistles);
                family_books_en = getNameFamilyBooks(PaulineEpistles, "en");
                family_books_ru = getNameFamilyBooks(PaulineEpistles, "ru");
                nextFamily = FamilyBooks::GospelsAndActs;
            }
            else if (index < FamilyBooks::CatholicEpistles) {
                vecFamilyBooks = getVectorFamilyBooks(CatholicEpistles);
                family_books_en = getNameFamilyBooks(CatholicEpistles, "en");
                family_books_ru = getNameFamilyBooks(CatholicEpistles, "ru");
                nextFamily = FamilyBooks::PaulineEpistles;
            }
            else if (index < FamilyBooks::Apocalypse) {
                vecFamilyBooks = getVectorFamilyBooks(Apocalypse);
                family_books_en = getNameFamilyBooks(Apocalypse, "en");
                family_books_ru = getNameFamilyBooks(Apocalypse, "ru");
                nextFamily = FamilyBooks::CatholicEpistles;
            }
            bookIndex = getIndexBookStr(index, BibleEnums::New_Testament, Standard::Western, requiredStandart);
            refObjTestament = &objNewTestament;
        }
        objBook.insert("name_ru", vecFamilyBooks.at(index - nextFamily));
        objBook.insert("family_books_en", family_books_en);
        objBook.insert("family_books_ru", family_books_ru);

        refObjTestament->insert(bookIndex, objBook);
        Q_ASSERT(!objBook.isEmpty());
    }
    FileWorker::writeFileJson(QJsonDocument(objOldTestament), Path::fileContent_Old_Testament_Info_KAZAKOV);
    FileWorker::writeFileJson(QJsonDocument(objNewTestament), Path::fileContent_New_Testament_Info_KAZAKOV);

    //    [
    //        {
    //        "chapter" : 1,
    //        "verse" : 1,
    //        "text" : "В начале сотворил Бог небо и землю.",
    //        "translation_id" : "RST",
    //        "book_id" : "Gen",
    //        "book_name" : "Genesis",
    //        },
    //        {
    //        ...
    //        },
    //    ]
}

void Content::generateContent_JsonText_BODRUK(const Standard requiredStandart)
{
    QJsonDocument doc;
    // Path::allBibleJsonText has the Standard::Western standart.
    FileWorker::readFileJson(&doc, Path::allBibleJsonText_BODRUK);
    QJsonArray arrMain = doc.array();

    QString dirContent { Path::dirContent_Old_Testament_JsonText_BODRUK };
    for (int var = 0; var < arrMain.size(); ++var) {
        QJsonObject objBook = arrMain.at(var).toObject();
        QJsonArray arrChapters = objBook.value("chapters").toArray();
        if (var < BibleEnums::Old_Testament) {
            const QString bookIndex = getIndexBookStr(var);
            FileWorker::writeFileJson(QJsonDocument(arrChapters), dirContent + bookIndex + ".json");
        }
        else{
            dirContent = Path::dirContent_New_Testament_JsonText_BODRUK;
            const QString bookIndex = getIndexBookStr(var, BibleEnums::New_Testament, Standard::Western, requiredStandart);
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

void Content::generateContent_JsonText_ONLINE(const Content::Standard requiredStandart)
{

}

void Content::generateContent_JsonText_KAZAKOV(const Content::Standard requiredStandart)
{
    QJsonDocument doc;
    // Path::allBibleJsonText has the Standard::Western standart.
    FileWorker::readFileJson(&doc, Path::tempJson);
    QJsonArray arrMain = doc.array();
    Q_ASSERT(!arrMain.isEmpty());

    QString dirContent { Path::dirContent_Old_Testament_JsonText_KAZAKOV };
    int index { 0 };
    QJsonArray arrChapters;
    QJsonArray arrVerses;
    for (int var = 0; var < arrMain.size(); ++var) {
        QJsonObject objBookVerse = arrMain.at(var).toObject();
        QJsonObject nextObjBookVerse = var + 1 < arrMain.size() ? arrMain.at(var + 1).toObject() : QJsonObject();
        const int currentChapter = objBookVerse.value("chapter").toInt();
        const QString currentBook = objBookVerse.value("book_name").toString();
        const int nextChapter = nextObjBookVerse.value("chapter").toInt();
        const QString nextBook = nextObjBookVerse.value("book_name").toString();
        arrVerses.append(objBookVerse.value("text"));
        if (currentChapter != nextChapter || currentBook != nextBook) {
            arrChapters.append(arrVerses);
            arrVerses = QJsonArray();
        }

        if (currentBook == nextBook && var + 1 < arrMain.size()) {
            continue;
        }
        if (var == arrMain.size() - 1) {
            arrChapters.append(arrVerses);
        }

        Q_ASSERT(!arrChapters.isEmpty());
        if (index < BibleEnums::Old_Testament) {
            const QString bookIndex = getIndexBookStr(index);
            FileWorker::writeFileJson(QJsonDocument(arrChapters), dirContent + bookIndex + ".json");
        }
        else{
            dirContent = Path::dirContent_New_Testament_JsonText_KAZAKOV;
            const QString bookIndex = getIndexBookStr(index, BibleEnums::New_Testament, Standard::Western, requiredStandart);
            qDebug() << "bookIndex" << bookIndex << currentBook <<
                        qPrintable(QJsonDocument(arrChapters).toJson(QJsonDocument::Compact)) << Qt::endl;
            FileWorker::writeFileJson(QJsonDocument(arrChapters), dirContent + bookIndex + ".json");
        }
        arrChapters = QJsonArray();
        ++index;
    }
    //    [
    //        {
    //        "chapter" : 1,
    //        "verse" : 1,
    //        "text" : "В начале сотворил Бог небо и землю.",
    //        "translation_id" : "RST",
    //        "book_id" : "Gen",
    //        "book_name" : "Genesis",
    //        },
    //        {
    //        ...
    //        },
    //    ]
}

void Content::generateContent_TwoArraysBooks(const TypeContent typeContent)
{
    const int Old_New_Testament { 2 };
    for (int var = 0; var < Old_New_Testament; ++var) {
        QString fileContentJsonText = var == 0 ? Path::fileContent_Old_Testament_Info_BODRUK : Path::fileContent_New_Testament_Info_BODRUK;
        QString fileContentArrayBooks = var == 0 ? Path::fileContent_Old_Testament_ArrayBooks_BODRUK : Path::fileContent_New_Testament_ArrayBooks_BODRUK;
        if (typeContent == TypeContent::BIBLEONLINE_RU) {
            fileContentJsonText = var == 0 ? Path::fileContent_Old_Testament_Info_ONLINE : Path::fileContent_New_Testament_Info_ONLINE;
            fileContentArrayBooks = var == 0 ? Path::fileContent_Old_Testament_ArrayBooks_ONLINE : Path::fileContent_New_Testament_ArrayBooks_ONLINE;
        }
        else if (typeContent == TypeContent::GITHUB_BIBLE_USFM2JSON_RUSLAN_KAZAKOV) {
            fileContentJsonText = var == 0 ? Path::fileContent_Old_Testament_Info_KAZAKOV : Path::fileContent_New_Testament_Info_KAZAKOV;
            fileContentArrayBooks = var == 0 ? Path::fileContent_Old_Testament_ArrayBooks_KAZAKOV : Path::fileContent_New_Testament_ArrayBooks_KAZAKOV;
        }

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
#endif

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
    const QString nameFile = testament == BibleEnums::Old_Testament ? Path::fileContent_Old_Testament_ArrayBooks_KAZAKOV : Path::fileContent_New_Testament_ArrayBooks_KAZAKOV;
    QJsonDocument doc;
    FileWorker::readFileJson(&doc, nameFile);
    QJsonArray arr = doc.array();
    std::for_each(arr.begin(), arr.end(), [list](const QJsonValue &value){ list->append(value.toString()); });
}

void Content::loadContenet_OneBook(Book *book, const BibleEnums::Testament testament)
{
    Q_ASSERT(book);
    const QString dirContent = testament == BibleEnums::Old_Testament ? Path::dirContent_Old_Testament_JsonText_KAZAKOV : Path::dirContent_New_Testament_JsonText_KAZAKOV;
    const QString pathBook = dirContent + getIndexBookStr(book->getIndexBook()) + ".json";
    QJsonDocument doc;
    FileWorker::readFileJson(&doc, pathBook);
    book->loadContentChapterText(doc.array());
}

void Content::loadTextVersesJson(QVector<Book> *vecBooks, const BibleEnums::Testament testament)
{
    const QString fileContent = testament == BibleEnums::Old_Testament ? Path::fileContent_Old_Testament_Info_KAZAKOV : Path::fileContent_New_Testament_Info_KAZAKOV;
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

QString Content::getIndexBookStr(int indexBook, const BibleEnums::Testament testament,
                                 const Content::Standard currentStandart, const Content::Standard requiredStandart)
{
    if (testament == BibleEnums::New_Testament && currentStandart != requiredStandart) {
        const int quantityCatholicEpistles { 7 };
        const int quantityPaulineEpistles { 14 };
        // Western --> EasternSynodal : Western <-- EasternSynodal
        const int firstFamily = requiredStandart == Standard::EasternSynodal ? quantityCatholicEpistles : quantityPaulineEpistles;
        const int lastFamily = requiredStandart == Standard::EasternSynodal ? quantityPaulineEpistles : quantityCatholicEpistles;
        if (indexBook >= FamilyBooks::GospelsAndActs && indexBook < FamilyBooks::GospelsAndActs + lastFamily) {
            indexBook += firstFamily;
        }
        else if(indexBook >= FamilyBooks::GospelsAndActs + lastFamily && indexBook < FamilyBooks::GospelsAndActs + lastFamily + firstFamily) {
            indexBook -= lastFamily;
        }
    }
    if (testament == BibleEnums::New_Testament) {
        indexBook -= BibleEnums::Old_Testament;
    }
    return getIndexBookStr(indexBook);
}

QVector<QString> Content::getVectorFamilyBooks(const Content::FamilyBooks familyBooks)
{
    QVector<QString> vecFamilyBooks;
    if (familyBooks == FamilyBooks::Pentateuch) {
        vecFamilyBooks = { "Бытие", "Исход", "Левит", "Числа", "Второзаконие" };
    }
    else if (familyBooks == FamilyBooks::HistoricalBooks) {
        vecFamilyBooks = { "Иисус Навин", "Судьи", "Руфь", "1 Царств", "2 Царств", "3 Царств", "4 Царств",
                           "1 Паралипомен", "2 Паралипомен", "Ездра", "Неемия", "Есфирь" };
    }
    else if (familyBooks == FamilyBooks::Wisdom) {
        vecFamilyBooks = { "Иов", "Псалтирь", "Притчи", "Екклеcиаст", "Песня песней" };
    }
    else if (familyBooks == FamilyBooks::MajorProphets) {
        vecFamilyBooks = { "Исаия", "Иеремия", "Плач Иеремии", "Иезекииль", "Даниил" };
    }
    else if (familyBooks == FamilyBooks::MinorProphets) {
        vecFamilyBooks = { "Осия", "Иоиль", "Амос", "Авдий", "Иона", "Михей", "Наум", "Аввакум", "Софония", "Аггей",
                           "Захария", "Малахия" };
    }
    else if (familyBooks == FamilyBooks::GospelsAndActs) {
        vecFamilyBooks = { "Матфея", "Марка", "Луки", "Иоанна", "Деяния" };
    }
    else if (familyBooks == FamilyBooks::PaulineEpistles) {
        vecFamilyBooks = { "Римлянам", "1 Коринфянам", "2 Коринфянам", "Галатам", "Ефесянам", "Филиппийцам", "Колоссянам",
                           "1 Фессалоникийцам", "2 Фессалоникийцам", "1 Тимофею", "2 Тимофею", "Титу", "Филимону", "Евреям"};
    }
    else if (familyBooks == FamilyBooks::CatholicEpistles) {
        vecFamilyBooks = { "Иакова", "1 Петра", "2 Петра", "1 Иоанна", "2 Иоанна", "3 Иоанна", "Иуда" };
    }
    else if (familyBooks == FamilyBooks::Apocalypse) {
        vecFamilyBooks = { "Откровение" };
    }
    return  vecFamilyBooks;
}

QString Content::getNameFamilyBooks(const Content::FamilyBooks familyBooks, const QString &language)
{
    QString family_books_en;
    QString family_books_ru;
    if (familyBooks == FamilyBooks::Pentateuch) {
        family_books_en = "Pentateuch";
        family_books_ru = "Пятикнижие";
    }
    else if (familyBooks == FamilyBooks::HistoricalBooks) {
        family_books_en = "Historical Books";
        family_books_ru = "Исторические";
    }
    else if (familyBooks == FamilyBooks::Wisdom) {
        family_books_en = "Wisdom";
        family_books_ru = "Учительные";
    }
    else if (familyBooks == FamilyBooks::MajorProphets) {
        family_books_en = "Major Prophets";
        family_books_ru = "Большие пророки";
    }
    else if (familyBooks == FamilyBooks::MinorProphets) {
        family_books_en = "Minor Prophets";
        family_books_ru = "Малые пророки";
    }
    else if (familyBooks == FamilyBooks::GospelsAndActs) {
        family_books_en = "Gospels and Acts";
        family_books_ru = "Евангелия и Деяния";
    }
    else if (familyBooks == FamilyBooks::PaulineEpistles) {
        family_books_en = "Pauline Epistles";
        family_books_ru = "Послания Павла";
    }
    else if (familyBooks == FamilyBooks::CatholicEpistles) {
        family_books_en = "Catholic Epistles";
        family_books_ru = "Соборные послания";
    }
    else if (familyBooks == FamilyBooks::Apocalypse) {
        family_books_en = "Apocalypse";
        family_books_ru = "Пророческие";
    }

    if (language.toLower() == "en") {
        return family_books_en;
    }
    return family_books_ru;
}

#ifdef QT_DEBUG
void Content::getOnlineBookList()
{
    const QString url { "https://api.bibleonline.ru/booklist" };
    const QJsonDocument docParam({
                                     { "callback", "bible" },
                                     { "trans", "rus" }
                                     //                                     { "trans", "lut" }
                                 });
    sendGetRequest(url, docParam.toJson(), std::bind(&Content::slotGetReply, std::placeholders::_1));
}

void Content::getOnlineBible()
{
    const QString url { "https://api.bibleonline.ru/bible" };
    const QJsonDocument docParam({
                                     { "callback", "bible" },
                                     { "trans", "rus" },
                                     { "max", "2" },
                                     { "q", "Genesis 3.3"}
                                 });
    sendGetRequest(url, docParam.toJson(), std::bind(&Content::slotGetReply, std::placeholders::_1));
}

void Content::generateValidJson_KAZAKOV()
{
    QByteArray arr;
    FileWorker::readFile(&arr, Path::allBibleJsonText_KAZAKOV);
    arr.replace("\"}\n", "\"},\n");
    arr.remove(arr.size() - 2, 2); // remove last ",\n"
    arr.insert(0, '[');
    arr.append(']');
    QJsonDocument doc = QJsonDocument::fromJson(arr);
    if (!doc.isEmpty()) {
        qDebug() << "doc is valid" << Qt::endl;
    }
    FileWorker::writeFile(arr, Path::tempJson);
}

void Content::sendGetRequest(const QString &urlStr, const QByteArray &paramJson, std::function<void (QNetworkReply *)> funcSlotReply)
{
    const QString header { "application/json" };
    qDebug() << "send param Utf8" << Qt::endl << qPrintable(QJsonDocument::fromJson(paramJson).toJson());
    QUrl url(urlStr);
    QUrlQuery query(paramJson);
    url.setQuery(query.query());
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, header);
    mngr.get(request);
    QObject::connect(&mngr, &QNetworkAccessManager::sslErrors, &Content::slotSSLErrors);
    QObject::connect(&mngr, &QNetworkAccessManager::finished, funcSlotReply);
}

void Content::slotSSLErrors(QNetworkReply *reply, const QList<QSslError> &errors)
{
    qDebug() << "error camera: " << errors << Qt::endl;
    reply->ignoreSslErrors(errors);
    QObject::disconnect(&mngr, &QNetworkAccessManager::sslErrors, nullptr, nullptr);
}

void Content::slotGetReply(QNetworkReply *reply)
{
    QByteArray arrReply { reply->readAll() };
    reply->deleteLater();
    QObject::disconnect(&mngr, &QNetworkAccessManager::finished, nullptr, nullptr);
    if(reply->error() != QNetworkReply::NoError){
        qWarning() << "reply->error()" << reply->error() << Qt::endl;
        return;
    }
    arrReply.remove(0, 1);
    arrReply.remove(arrReply.size() - 2, 2);
    QJsonDocument doc = QJsonDocument::fromJson(arrReply);
    qDebug() << "Response from server: " << Qt::endl << qPrintable(doc.toJson(QJsonDocument::Indented));
    if (doc.isEmpty()) {
        qDebug() << "arrReply" << arrReply << Qt::endl;
    }
    FileWorker::writeFileJson(doc, Path::tempJson);
}
#endif

