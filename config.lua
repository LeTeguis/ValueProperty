
-- ValueProperty Config

Externals = {}

Internals = {}
Internals["ValueProperty"]      = "%{wks.location}/ValueProperty"
Internals["Logger"]             = "%{wks.location}/Utils/Logger/Logger"
Internals["UTest"]              = "%{wks.location}/Utils/UTest"
Internals["Float"]              = "%{wks.location}/UTest/Float"
Internals["Integer"]            = "%{wks.location}/UTest/Integer"
Internals["String"]             = "%{wks.location}/UTest/String"
Internals["Personalyse"]        = "%{wks.location}/UTest/Personalyse"
Internals["AllExemple"]         = "%{wks.location}/UTest/AllExemple"
Internals["AllTest"]            = "%{wks.location}/Test/AllTest"

InternalBuilds = {}

newoption {
    trigger         = "libtype",
    value           = "STATIC_LIB",
    description     = "ce flag peut prendre les valeur {STATIC_LIB ou DYNAMIC_LIB}",
    default         = "STATIC_LIB",
    category        = "Lib",
    allowed         = {
        {"STATIC_LIB", "STATIC LIB"},
        {"DYNAMIC_LIB", "DYNAMIC LIB"}
    }
}

function getLibraryType()
	libtype = _OPTIONS["libtype"]

    if libtype == "DYNAMIC_LIB" then
        return "SharedLib"
    else
        return "StaticLib"
    end
end

libraryType = getLibraryType()
