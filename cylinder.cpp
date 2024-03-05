#include "CATIAApplicationFrame.h"
#include "CATIPartDocument.h"
#include "CATIPart.h"
#include "CATIBody.h"
#include "CATICreateCylinder.h"

int main(int argc, char* argv[])
{
    // Initialize COM library
    HRESULT hr = CoInitialize(NULL);
    if (FAILED(hr))
    {
        cout << "Failed to initialize COM library." << endl;
        return -1;
    }

    try
    {
        // Obtain the CATIA application frame
        CATIAApplicationFrame appFrame;
        IApplicationPtr spApplication = appFrame.GetApplication();
        if (spApplication == nullptr)
        {
            throw std::runtime_error("CATIA application not found.");
        }

        // Create a new Part document
        IDocumentsPtr spDocuments = spApplication->Documents;
        IPartDocumentPtr spPartDoc = spDocuments->Add("Part");
        if (spPartDoc == nullptr)
        {
            throw std::runtime_error("Failed to create a new Part document.");
        }

        // Get the Part component from the document
        IPartPtr spPart = spPartDoc->Part;
        if (spPart == nullptr)
        {
            throw std::runtime_error("Failed to get Part from the document.");
        }

        // Create a new body for the cylinder
        IBodiesPtr spBodies = spPart->Bodies;
        IBodyPtr spBody = spBodies->Add();
        if (spBody == nullptr)
        {
            throw std::runtime_error("Failed to create a new body.");
        }
        spPart->InWorkObject = spBody; // Set the created body as the in-work object

        // Create a cylinder
        ICATICreateCylinderPtr spCreateCylinder = spBody->Shapes->AddNewCylinder();
        spCreateCylinder->Radius = 6; // Diameter is 12mm, so radius is half of that
        spCreateCylinder->Height = 10; // Depth (height) of the cylinder
        spCreateCylinder->Axis = ...; // Specify the axis of the cylinder (you need to define it based on your requirements)

        // Update the part to reflect the new geometry
        spPart->Update();

        cout << "Cylinder created successfully in CATIA." << endl;
    }
    catch (const std::exception& e)
    {
        cout << "Error: " << e.what() << endl;
    }

    // Uninitialize COM library
    CoUninitialize();

    return 0;
}
