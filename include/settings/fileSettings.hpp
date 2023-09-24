#ifndef _FILE_SETTINGS_HPP_

#define _FILE_SETTINGS_HPP_

#include "defaults.hpp"

#include <string>        // for string, allocator
#include <string_view>   // for string_view

namespace settings
{
    /**
     * @class FileSettings
     *
     * @brief static class to store settings of the files
     *
     */
    class FileSettings
    {
      private:
        static inline std::string _molDescriptorFileName = defaults::_MOLDESCRIPTOR_FILENAME_DEFAULT_;
        static inline std::string _guffDatFileName       = defaults::_GUFF_FILENAME_DEFAULT_;
        static inline std::string _topologyFileName;
        static inline std::string _parameterFileName;
        static inline std::string _intraNonBondedFileName;
        static inline std::string _startFileName;
        static inline std::string _ringPolymerStartFileName;

        static bool inline _isTopologyFileNameSet         = false;
        static bool inline _isParameterFileNameSet        = false;
        static bool inline _isIntraNonBondedFileNameSet   = false;
        static bool inline _isRingPolymerStartFileNameSet = false;

      public:
        FileSettings()  = default;
        ~FileSettings() = default;

        /********************
         * standard getters *
         ********************/

        [[nodiscard]] static std::string getMolDescriptorFileName() { return _molDescriptorFileName; }
        [[nodiscard]] static std::string getGuffDatFileName() { return _guffDatFileName; }
        [[nodiscard]] static std::string getTopologyFileName() { return _topologyFileName; }
        [[nodiscard]] static std::string getParameterFilename() { return _parameterFileName; }
        [[nodiscard]] static std::string getIntraNonBondedFileName() { return _intraNonBondedFileName; }
        [[nodiscard]] static std::string getStartFileName() { return _startFileName; }
        [[nodiscard]] static std::string getRingPolymerStartFileName() { return _ringPolymerStartFileName; }

        [[nodiscard]] static bool isTopologyFileNameSet() { return _isTopologyFileNameSet; }
        [[nodiscard]] static bool isParameterFileNameSet() { return _isParameterFileNameSet; }
        [[nodiscard]] static bool isIntraNonBondedFileNameSet() { return _isIntraNonBondedFileNameSet; }
        [[nodiscard]] static bool isRingPolymerStartFileNameSet() { return _isRingPolymerStartFileNameSet; }

        /********************
         * standard setters *
         ********************/

        static void setMolDescriptorFileName(const std::string_view name) { FileSettings::_molDescriptorFileName = name; }
        static void setGuffDatFileName(const std::string_view name) { FileSettings::_guffDatFileName = name; }
        static void setTopologyFileName(const std::string_view name) { FileSettings::_topologyFileName = name; }
        static void setParameterFileName(const std::string_view name) { FileSettings::_parameterFileName = name; }
        static void setIntraNonBondedFileName(const std::string_view name) { FileSettings::_intraNonBondedFileName = name; }
        static void setStartFileName(const std::string_view name) { FileSettings::_startFileName = name; }
        static void setRingPolymerStartFileName(const std::string_view name) { FileSettings::_ringPolymerStartFileName = name; }

        static void setIsTopologyFileNameSet() { FileSettings::_isTopologyFileNameSet = true; }
        static void setIsParameterFileNameSet() { FileSettings::_isParameterFileNameSet = true; }
        static void setIsIntraNonBondedFileNameSet() { FileSettings::_isIntraNonBondedFileNameSet = true; }
        static void setIsRingPolymerStartFileNameSet() { FileSettings::_isRingPolymerStartFileNameSet = true; }

        static void unsetIsTopologyFileNameSet() { FileSettings::_isTopologyFileNameSet = false; }
        static void unsetIsParameterFileNameSet() { FileSettings::_isParameterFileNameSet = false; }
        static void unsetIsIntraNonBondedFileNameSet() { FileSettings::_isIntraNonBondedFileNameSet = false; }
        static void unsetIsRingPolymerStartFileNameSet() { FileSettings::_isRingPolymerStartFileNameSet = false; }
    };

}   // namespace settings

#endif   // _FILE_SETTINGS_HPP_