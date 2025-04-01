#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QString>

#include <QDomDocument>
#include <QDomElement>
#include <QDomNodeList>
#include <QDomNode>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    qInfo() << "--- Starting XML Attribute Parsing Example ---";

    // --- Sample XML with attributes ---
    QString xmlContent = R"(
        <catalog>
            <product id="101" name="Chocolate Chip Cookie" type="food"/>
            <product id="205" name="Gummy Bears" type="food" stock="low"/>
            <product id="310" name="Screwdriver Set" type="tool"/>
            <product id="404" name="Laptop Stand" type="accessory" stock="high"/>
        </catalog>
    )";

    // --- Optional: Load from file (e.g., catalog.xml) ---
    /*
    QFile file("catalog.xml");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Error: Could not open XML file:" << file.errorString();
        return 1;
    }
    QString xmlContent = file.readAll();
    file.close();
    */
    // ------------------------------------------------------


    QDomDocument xmlDoc;
    QString errorMsg;
    int errorLine, errorColumn;
    if (!xmlDoc.setContent(xmlContent, &errorMsg, &errorLine, &errorColumn)) {
        qWarning() << "Error parsing XML content:" << errorMsg
                   << "at line" << errorLine << ", column" << errorColumn;
        return 1;
    }

    QDomElement rootElement = xmlDoc.documentElement();
    if (rootElement.isNull() || rootElement.tagName() != "catalog") { // Check for the correct root
        qWarning() << "Error: Could not find root <catalog> element.";
        return 1;
    }

    qInfo() << "Successfully parsed XML. Root element:" << rootElement.tagName();

    // Find all <product> elements under the root
    QDomNodeList productNodes = rootElement.elementsByTagName("product");

    qInfo() << "Found" << productNodes.count() << "product(s). Processing...";

    // Iterate through the found <product> nodes
    for (int i = 0; i < productNodes.count(); ++i) {
        QDomNode node = productNodes.at(i);

        if (node.isElement()) {
            QDomElement productElement = node.toElement(); // Convert node to element

            // *** Use the attribute() method to get attribute values ***
            QString id = productElement.attribute("id", "N/A"); // Get 'id', default to "N/A" if missing
            QString name = productElement.attribute("name", "Unknown"); // Get 'name', default to "Unknown"
            QString type = productElement.attribute("type"); // Get 'type', empty string if missing
            QString stock = productElement.attribute("stock", "medium"); // Get optional 'stock', default to "medium"

            // You might want to convert the ID to an integer if needed
            bool conversionOk = false;
            int idInt = id.toInt(&conversionOk);
            if (!conversionOk && id != "N/A") {
                qWarning() << "Warning: Could not convert product ID '" << id << "' to integer.";
                idInt = -1; // Or handle error appropriately
            }


            // Print the extracted attribute data
            qInfo().noquote() << QString("  Product %1: ID=%2 (int: %3), Name='%4', Type='%5', Stock='%6'")
                                     .arg(i + 1)
                                     .arg(id) // The original string ID
                                     .arg(idInt) // The converted integer ID
                                     .arg(name)
                                     .arg(type)
                                     .arg(stock);

            // --- Example: Find a specific product by attribute ---
            if (name == "Screwdriver Set") {
                qInfo() << "    -> Found the specific 'Screwdriver Set'!";
            }
            if (id == "205") {
                qInfo() << "    -> Found product with ID 205!";
            }
        }
    }

    qInfo() << "--- XML Attribute Parsing Example Finished ---";

    return 0;
}
