/* =========================================================================================

   This is an auto-generated file, created by The Introjucer 3.0.0
   Do not edit anything in this file!

*/

namespace BinaryData
{
    extern const char*   gpxdbimporterexporter_icon_png;
    const int            gpxdbimporterexporter_icon_pngSize = 124549;

    extern const char*   citydefs_gml;
    const int            citydefs_gmlSize = 120104;

    extern const char*   locations_csv;
    const int            locations_csvSize = 7876;

    extern const char*   create_tables_sql;
    const int            create_tables_sqlSize = 1059;

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes) throw();

    //==============================================================================
    // This class acts as an ImageProvider that will access the BinaryData images
    class ImageProvider  : public juce::ComponentBuilder::ImageProvider
    {
    public:
        ImageProvider() noexcept {}

        juce::Image getImageForIdentifier (const juce::var& imageIdentifier)
        {
            int dataSize = 0;
            const char* const data = getNamedResource (imageIdentifier.toString().toUTF8(), dataSize);

            if (data != nullptr)
                return juce::ImageCache::getFromMemory (data, dataSize);

            return juce::Image();
        }

        juce::var getIdentifierForImage (const juce::Image&)  { return juce::var(); }
    };
}
