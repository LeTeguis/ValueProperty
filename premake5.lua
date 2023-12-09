include "config.lua"

workspace "ValueProperty"
	architecture "x86_64"
	startproject "AllExemple"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
build = "%{wks.location}/build/"
build_int = "%{wks.location}/build-int/"

group "Utils"
    include "Utils/Logger/Logger"
    include "Utils/UTest"
group ""

group "Core"
	include "ValueProperty"
group ""

group "UTest"
	include "Test/AllTest"
group ""

group "Exemples"
	include "Exemples/Float"
	include "Exemples/Integer"
	include "Exemples/String"
	include "Exemples/Personalyse"
	include "Exemples/AllExemple"
group ""