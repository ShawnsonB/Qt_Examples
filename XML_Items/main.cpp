#include <QCoreApplication> // Basic Qt functionality (console app)
#include <QDebug>         // For printing output
#include <QFile>          // To potentially read from a file
#include <QString>        // Qt's string class

// Core XML classes from the QtXml module
#include <QDomDocument>
#include <QDomElement>
#include <QDomNodeList>
#include <QDomNode>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    qInfo() << "--- Starting XML Parsing Example ---";

    // --- Option 1: XML content directly in a string ---
    QString xmlContent = R"(
        <inventory>
            <item category="gadget">
                <name>Smart Watch</name>
                <quantity>15</quantity>
                <price>199.99</price>
            </item>
            <item category="tool">
                <name>Wrench Set</name>
                <quantity>5</quantity>
                <price>75.50</price>
            </item>
            <item category="gadget">
                <name>Wireless Earbuds</name>
                <quantity>50</quantity>
                <price>89.00</price>
            </item>
        </inventory>
    )";

    // --- Option 2: Load XML from a file (Uncomment if you have data.xml) ---
    /*
    QFile file("data.xml");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Error: Could not open XML file:" << file.errorString();
        return 1;
    }
    QString xmlContent = file.readAll();
    file.close();
    */
    // --------------------------------------------------------------------


    // 1. Create a QDomDocument - this will hold the XML structure
    QDomDocument xmlDoc;

    // 2. Set the content - Parse the XML string
    QString errorMsg;
    int errorLine, errorColumn;
    if (!xmlDoc.setContent(xmlContent, &errorMsg, &errorLine, &errorColumn)) {
        qWarning() << "Error parsing XML content:" << errorMsg
                   << "at line" << errorLine << ", column" << errorColumn;
        return 1; // Exit if parsing failed
    }

    // 3. Get the root element (the outermost tag, <inventory> in our case)
    QDomElement rootElement = xmlDoc.documentElement();
    if (rootElement.isNull() || rootElement.tagName() != "inventory") {
        qWarning() << "Error: Could not find root <inventory> element.";
        return 1;
    }

    qInfo() << "Successfully parsed XML. Root element:" << rootElement.tagName();

    // 4. Find specific items - let's find all <item> elements
    //    elementsByTagName finds *all* elements with that name anywhere
    //    under the current element (here, the root).
    QDomNodeList itemNodes = rootElement.elementsByTagName("item");

    qInfo() << "Found" << itemNodes.count() << "item(s). Processing...";

    // 5. Iterate through the found <item> nodes
    for (int i = 0; i < itemNodes.count(); ++i) {
        QDomNode node = itemNodes.at(i);

        // Make sure it's actually an element (not a comment, text node etc.)
        if (node.isElement()) {
            QDomElement itemElement = node.toElement(); // Convert node to element

            // Get an attribute value (e.g., the 'category')
            QString category = itemElement.attribute("category", "unknown"); // Default value if attr missing

            // Find child elements within this <item>
            // firstChildElement() is convenient if you expect only one tag of that name
            QDomElement nameElement = itemElement.firstChildElement("name");
            QDomElement quantityElement = itemElement.firstChildElement("quantity");
            QDomElement priceElement = itemElement.firstChildElement("price");

            // Extract the text content from the child elements
            QString name = "N/A";
            int quantity = 0;
            double price = 0.0;

            if (!nameElement.isNull()) {
                name = nameElement.text(); // Get text between <name>...</name>
            }
            if (!quantityElement.isNull()) {
                quantity = quantityElement.text().toInt(); // Convert text to integer
            }
            if (!priceElement.isNull()) {
                price = priceElement.text().toDouble(); // Convert text to double
            }

            // Print the extracted data
            qInfo().noquote() << QString("  Item %1: Name='%2', Quantity=%3, Price=%4, Category='%5'")
                                     .arg(i + 1)
                                     .arg(name)
                                     .arg(quantity)
                                     .arg(price)
                                     .arg(category);

            // --- Example: Find a *specific* item ---
            if (name == "Wrench Set") {
                qInfo() << "    -> Found the specific 'Wrench Set'!";
            }
        }
    }

    qInfo() << "--- XML Parsing Example Finished ---";

    // return a.exec(); // Not strictly needed for a simple console app that just prints
    return 0; // Success
}
