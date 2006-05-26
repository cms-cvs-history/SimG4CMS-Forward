#include "SimG4CMS/Forward/interface/CastorSD.h"
#include "SimG4CMS/Forward/interface/TotemSD.h"
#include "SimG4CMS/Forward/interface/ZdcSD.h"
#include "SimG4CMS/Forward/interface/TotemTestGem.h"
#include "SimG4CMS/Forward/interface/ZdcTestAnalysis.h"
#include "SimG4Core/SensitiveDetector/interface/SensitiveDetectorPluginFactory.h"
#include "SimG4Core/Watcher/interface/SimWatcherFactory.h"
#include "PluginManager/ModuleDef.h"
  
DEFINE_SEAL_MODULE ();
typedef CastorSD CastorSensitiveDetector;
DEFINE_SENSITIVEDETECTOR(CastorSensitiveDetector);
typedef TotemSD TotemSensitiveDetector;
DEFINE_SENSITIVEDETECTOR(TotemSensitiveDetector);
typedef ZdcSD ZdcSensitiveDetector;
DEFINE_SENSITIVEDETECTOR(ZdcSensitiveDetector);
DEFINE_SIMWATCHER (ZdcTestAnalysis);
DEFINE_SIMWATCHER (TotemTestGem);
