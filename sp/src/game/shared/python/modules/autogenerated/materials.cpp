// This file has been generated by Py++.

#include "cbase.h"
#ifdef CLIENT_DLL
#include "cbase.h"

#include "materialsystem/imaterial.h"

#include "materialsystem/MaterialSystemUtil.h"

#include "python/srcpy_materials.h"

#include "view_shared.h"

#include "cdll_client_int.h"

#include "viewpostprocess.h"

#include "glow_outline_effect.h"

#include "tier0/valve_minmax_off.h"

#include "srcpy.h"

#include "tier0/valve_minmax_on.h"

#include "tier0/memdbgon.h"

namespace bp = boost::python;

BOOST_PYTHON_MODULE(materials){
    bp::docstring_options doc_options( true, true, false );

    bp::enum_< ImageFormat>("ImageFormat")
        .value("IMAGE_FORMAT_UNKNOWN", IMAGE_FORMAT_UNKNOWN)
        .value("IMAGE_FORMAT_RGBA8888", IMAGE_FORMAT_RGBA8888)
        .value("IMAGE_FORMAT_ABGR8888", IMAGE_FORMAT_ABGR8888)
        .value("IMAGE_FORMAT_RGB888", IMAGE_FORMAT_RGB888)
        .value("IMAGE_FORMAT_BGR888", IMAGE_FORMAT_BGR888)
        .value("IMAGE_FORMAT_RGB565", IMAGE_FORMAT_RGB565)
        .value("IMAGE_FORMAT_I8", IMAGE_FORMAT_I8)
        .value("IMAGE_FORMAT_IA88", IMAGE_FORMAT_IA88)
        .value("IMAGE_FORMAT_P8", IMAGE_FORMAT_P8)
        .value("IMAGE_FORMAT_A8", IMAGE_FORMAT_A8)
        .value("IMAGE_FORMAT_RGB888_BLUESCREEN", IMAGE_FORMAT_RGB888_BLUESCREEN)
        .value("IMAGE_FORMAT_BGR888_BLUESCREEN", IMAGE_FORMAT_BGR888_BLUESCREEN)
        .value("IMAGE_FORMAT_ARGB8888", IMAGE_FORMAT_ARGB8888)
        .value("IMAGE_FORMAT_BGRA8888", IMAGE_FORMAT_BGRA8888)
        .value("IMAGE_FORMAT_DXT1", IMAGE_FORMAT_DXT1)
        .value("IMAGE_FORMAT_DXT3", IMAGE_FORMAT_DXT3)
        .value("IMAGE_FORMAT_DXT5", IMAGE_FORMAT_DXT5)
        .value("IMAGE_FORMAT_BGRX8888", IMAGE_FORMAT_BGRX8888)
        .value("IMAGE_FORMAT_BGR565", IMAGE_FORMAT_BGR565)
        .value("IMAGE_FORMAT_BGRX5551", IMAGE_FORMAT_BGRX5551)
        .value("IMAGE_FORMAT_BGRA4444", IMAGE_FORMAT_BGRA4444)
        .value("IMAGE_FORMAT_DXT1_ONEBITALPHA", IMAGE_FORMAT_DXT1_ONEBITALPHA)
        .value("IMAGE_FORMAT_BGRA5551", IMAGE_FORMAT_BGRA5551)
        .value("IMAGE_FORMAT_UV88", IMAGE_FORMAT_UV88)
        .value("IMAGE_FORMAT_UVWQ8888", IMAGE_FORMAT_UVWQ8888)
        .value("IMAGE_FORMAT_RGBA16161616F", IMAGE_FORMAT_RGBA16161616F)
        .value("IMAGE_FORMAT_RGBA16161616", IMAGE_FORMAT_RGBA16161616)
        .value("IMAGE_FORMAT_UVLX8888", IMAGE_FORMAT_UVLX8888)
        .value("IMAGE_FORMAT_R32F", IMAGE_FORMAT_R32F)
        .value("IMAGE_FORMAT_RGB323232F", IMAGE_FORMAT_RGB323232F)
        .value("IMAGE_FORMAT_RGBA32323232F", IMAGE_FORMAT_RGBA32323232F)
        .value("IMAGE_FORMAT_NV_DST16", IMAGE_FORMAT_NV_DST16)
        .value("IMAGE_FORMAT_NV_DST24", IMAGE_FORMAT_NV_DST24)
        .value("IMAGE_FORMAT_NV_INTZ", IMAGE_FORMAT_NV_INTZ)
        .value("IMAGE_FORMAT_NV_RAWZ", IMAGE_FORMAT_NV_RAWZ)
        .value("IMAGE_FORMAT_ATI_DST16", IMAGE_FORMAT_ATI_DST16)
        .value("IMAGE_FORMAT_ATI_DST24", IMAGE_FORMAT_ATI_DST24)
        .value("IMAGE_FORMAT_NV_NULL", IMAGE_FORMAT_NV_NULL)
        .value("IMAGE_FORMAT_ATI2N", IMAGE_FORMAT_ATI2N)
        .value("IMAGE_FORMAT_ATI1N", IMAGE_FORMAT_ATI1N)
        .value("IMAGE_FORMAT_DXT1_RUNTIME", IMAGE_FORMAT_DXT1_RUNTIME)
        .value("IMAGE_FORMAT_DXT5_RUNTIME", IMAGE_FORMAT_DXT5_RUNTIME)
        .value("NUM_IMAGE_FORMATS", NUM_IMAGE_FORMATS)
        .export_values()
        ;

    bp::class_< CGlowObjectManager, boost::noncopyable >( "CGlowObjectManager", bp::no_init )    
        .def( bp::init< >() )    
        .def( 
            "HasGlowEffect"
            , (bool ( ::CGlowObjectManager::* )( ::C_BaseEntity * )const)( &::CGlowObjectManager::HasGlowEffect )
            , ( bp::arg("pEntity") ) )    
        .def( 
            "IsRenderingWhenOccluded"
            , (bool ( ::CGlowObjectManager::* )( int )const)( &::CGlowObjectManager::IsRenderingWhenOccluded )
            , ( bp::arg("nGlowObjectHandle") ) )    
        .def( 
            "IsRenderingWhenUnoccluded"
            , (bool ( ::CGlowObjectManager::* )( int )const)( &::CGlowObjectManager::IsRenderingWhenUnoccluded )
            , ( bp::arg("nGlowObjectHandle") ) )    
        .def( 
            "RegisterGlowObject"
            , (int ( ::CGlowObjectManager::* )( ::C_BaseEntity *,::Vector const &,float,bool,bool,int ))( &::CGlowObjectManager::RegisterGlowObject )
            , ( bp::arg("pEntity"), bp::arg("vGlowColor"), bp::arg("flGlowAlpha"), bp::arg("bRenderWhenOccluded"), bp::arg("bRenderWhenUnoccluded"), bp::arg("nSplitScreenSlot") ) )    
        .def( 
            "RenderGlowEffects"
            , (void ( ::CGlowObjectManager::* )( ::CViewSetup const *,int ))( &::CGlowObjectManager::RenderGlowEffects )
            , ( bp::arg("pSetup"), bp::arg("nSplitScreenSlot") ) )    
        .def( 
            "SetAlpha"
            , (void ( ::CGlowObjectManager::* )( int,float ))( &::CGlowObjectManager::SetAlpha )
            , ( bp::arg("nGlowObjectHandle"), bp::arg("flAlpha") ) )    
        .def( 
            "SetColor"
            , (void ( ::CGlowObjectManager::* )( int,::Vector const & ))( &::CGlowObjectManager::SetColor )
            , ( bp::arg("nGlowObjectHandle"), bp::arg("vGlowColor") ) )    
        .def( 
            "SetEntity"
            , (void ( ::CGlowObjectManager::* )( int,::C_BaseEntity * ))( &::CGlowObjectManager::SetEntity )
            , ( bp::arg("nGlowObjectHandle"), bp::arg("pEntity") ) )    
        .def( 
            "SetRenderFlags"
            , (void ( ::CGlowObjectManager::* )( int,bool,bool ))( &::CGlowObjectManager::SetRenderFlags )
            , ( bp::arg("nGlowObjectHandle"), bp::arg("bRenderWhenOccluded"), bp::arg("bRenderWhenUnoccluded") ) )    
        .def( 
            "UnregisterGlowObject"
            , (void ( ::CGlowObjectManager::* )( int ))( &::CGlowObjectManager::UnregisterGlowObject )
            , ( bp::arg("nGlowObjectHandle") ) );

    { //::CMaterialReference
        typedef bp::class_< CMaterialReference > CMaterialReference_exposer_t;
        CMaterialReference_exposer_t CMaterialReference_exposer = CMaterialReference_exposer_t( "CMaterialReference", bp::init< bp::optional< char const *, char const *, bool > >(( bp::arg("pMaterialName")=bp::object(), bp::arg("pTextureGroupName")=bp::object(), bp::arg("bComplain")=(bool)(true) )) );
        bp::scope CMaterialReference_scope( CMaterialReference_exposer );
        bp::implicitly_convertible< char const *, CMaterialReference >();
        { //::CMaterialReference::Init
        
            typedef void ( ::CMaterialReference::*Init_function_type)( char const *,char const *,bool ) ;
            
            CMaterialReference_exposer.def( 
                "Init"
                , Init_function_type( &::CMaterialReference::Init )
                , ( bp::arg("pMaterialName"), bp::arg("pTextureGroupName"), bp::arg("bComplain")=(bool)(true) ) );
        
        }
        { //::CMaterialReference::Init
        
            typedef void ( ::CMaterialReference::*Init_function_type)( char const *,::KeyValues * ) ;
            
            CMaterialReference_exposer.def( 
                "Init"
                , Init_function_type( &::CMaterialReference::Init )
                , ( bp::arg("pMaterialName"), bp::arg("pVMTKeyValues") ) );
        
        }
        { //::CMaterialReference::Init
        
            typedef void ( ::CMaterialReference::*Init_function_type)( ::IMaterial * ) ;
            
            CMaterialReference_exposer.def( 
                "Init"
                , Init_function_type( &::CMaterialReference::Init )
                , ( bp::arg("pMaterial") ) );
        
        }
        { //::CMaterialReference::Init
        
            typedef void ( ::CMaterialReference::*Init_function_type)( ::CMaterialReference & ) ;
            
            CMaterialReference_exposer.def( 
                "Init"
                , Init_function_type( &::CMaterialReference::Init )
                , ( bp::arg("ref") ) );
        
        }
        { //::CMaterialReference::Init
        
            typedef void ( ::CMaterialReference::*Init_function_type)( char const *,char const *,::KeyValues * ) ;
            
            CMaterialReference_exposer.def( 
                "Init"
                , Init_function_type( &::CMaterialReference::Init )
                , ( bp::arg("pMaterialName"), bp::arg("pTextureGroupName"), bp::arg("pVMTKeyValues") ) );
        
        }
        { //::CMaterialReference::IsValid
        
            typedef bool ( ::CMaterialReference::*IsValid_function_type)(  ) ;
            
            CMaterialReference_exposer.def( 
                "IsValid"
                , IsValid_function_type( &::CMaterialReference::IsValid ) );
        
        }
        { //::CMaterialReference::Shutdown
        
            typedef void ( ::CMaterialReference::*Shutdown_function_type)(  ) ;
            
            CMaterialReference_exposer.def( 
                "Shutdown"
                , Shutdown_function_type( &::CMaterialReference::Shutdown ) );
        
        }
    }

    bp::class_< LightDesc_t >( "LightDesc_t", bp::init< >() )    
        .def( bp::init< Vector const &, Vector const & >(( bp::arg("pos"), bp::arg("color") )) )    
        .def( bp::init< Vector const &, Vector const &, Vector const &, float, float >(( bp::arg("pos"), bp::arg("color"), bp::arg("point_at"), bp::arg("inner_cone_boundary"), bp::arg("outer_cone_boundary") )) )    
        .def( 
            "ComputeLightAtPoints"
            , (void ( ::LightDesc_t::* )( ::FourVectors const &,::FourVectors const &,::FourVectors &,bool )const)( &::LightDesc_t::ComputeLightAtPoints )
            , ( bp::arg("pos"), bp::arg("normal"), bp::arg("color"), bp::arg("DoHalfLambert")=(bool)(false) ) )    
        .def( 
            "ComputeLightAtPointsForDirectional"
            , (void ( ::LightDesc_t::* )( ::FourVectors const &,::FourVectors const &,::FourVectors &,bool )const)( &::LightDesc_t::ComputeLightAtPointsForDirectional )
            , ( bp::arg("pos"), bp::arg("normal"), bp::arg("color"), bp::arg("DoHalfLambert")=(bool)(false) ) )    
        .def( 
            "ComputeNonincidenceLightAtPoints"
            , (void ( ::LightDesc_t::* )( ::FourVectors const &,::FourVectors & )const)( &::LightDesc_t::ComputeNonincidenceLightAtPoints )
            , ( bp::arg("pos"), bp::arg("color") ) )    
        .def( 
            "InitDirectional"
            , (void ( ::LightDesc_t::* )( ::Vector const &,::Vector const & ))( &::LightDesc_t::InitDirectional )
            , ( bp::arg("dir"), bp::arg("color") ) )    
        .def( 
            "InitPoint"
            , (void ( ::LightDesc_t::* )( ::Vector const &,::Vector const & ))( &::LightDesc_t::InitPoint )
            , ( bp::arg("pos"), bp::arg("color") ) )    
        .def( 
            "InitSpot"
            , (void ( ::LightDesc_t::* )( ::Vector const &,::Vector const &,::Vector const &,float,float ))( &::LightDesc_t::InitSpot )
            , ( bp::arg("pos"), bp::arg("color"), bp::arg("point_at"), bp::arg("inner_cone_boundary"), bp::arg("outer_cone_boundary") ) )    
        .def( 
            "IsDirectionWithinLightCone"
            , (bool ( ::LightDesc_t::* )( ::Vector const & )const)( &::LightDesc_t::IsDirectionWithinLightCone )
            , ( bp::arg("rdir") ) )    
        .def( 
            "OneOverThetaDotMinusPhiDot"
            , (float ( ::LightDesc_t::* )(  )const)( &::LightDesc_t::OneOverThetaDotMinusPhiDot ) )    
        .def( 
            "RecalculateDerivedValues"
            , (void ( ::LightDesc_t::* )(  ))( &::LightDesc_t::RecalculateDerivedValues ) )    
        .def( 
            "SetupNewStyleAttenuation"
            , (void ( ::LightDesc_t::* )( float,float ))( &::LightDesc_t::SetupNewStyleAttenuation )
            , ( bp::arg("fFiftyPercentDistance"), bp::arg("fZeroPercentDistance") ) )    
        .def( 
            "SetupOldStyleAttenuation"
            , (void ( ::LightDesc_t::* )( float,float,float ))( &::LightDesc_t::SetupOldStyleAttenuation )
            , ( bp::arg("fQuadatricAttn"), bp::arg("fLinearAttn"), bp::arg("fConstantAttn") ) )    
        .def_readwrite( "m_Attenuation0", &LightDesc_t::m_Attenuation0 )    
        .def_readwrite( "m_Attenuation1", &LightDesc_t::m_Attenuation1 )    
        .def_readwrite( "m_Attenuation2", &LightDesc_t::m_Attenuation2 )    
        .def_readwrite( "m_Color", &LightDesc_t::m_Color )    
        .def_readwrite( "m_Direction", &LightDesc_t::m_Direction )    
        .def_readwrite( "m_Falloff", &LightDesc_t::m_Falloff )    
        .def_readwrite( "m_Flags", &LightDesc_t::m_Flags )    
        .def_readwrite( "m_Phi", &LightDesc_t::m_Phi )    
        .def_readwrite( "m_PhiDot", &LightDesc_t::m_PhiDot )    
        .def_readwrite( "m_Position", &LightDesc_t::m_Position )    
        .def_readwrite( "m_Range", &LightDesc_t::m_Range )    
        .def_readwrite( "m_Theta", &LightDesc_t::m_Theta )    
        .def_readwrite( "m_ThetaDot", &LightDesc_t::m_ThetaDot )    
        .def_readwrite( "m_Type", &LightDesc_t::m_Type );

    bp::scope().attr( "glowobjectmanager" ) = boost::ref(g_GlowObjectManager);

    bp::class_< PyProceduralTexture, boost::noncopyable >( "ProceduralTexture", bp::init< char const *, char const *, int, int, ImageFormat, int >(( bp::arg("pTextureName"), bp::arg("pTextureGroupName"), bp::arg("w"), bp::arg("h"), bp::arg("fmt"), bp::arg("nFlags") )) )    
        .def( 
            "Download"
            , (void ( ::PyProceduralTexture::* )(  ))( &::PyProceduralTexture::Download ) )    
        .def( 
            "GetDebugID"
            , (int ( ::PyProceduralTexture::* )(  ))( &::PyProceduralTexture::GetDebugID ) )    
        .def( 
            "GetName"
            , (char const * ( ::PyProceduralTexture::* )(  ))( &::PyProceduralTexture::GetName ) )    
        .def( 
            "IsModified"
            , (bool ( ::PyProceduralTexture::* )(  ))( &::PyProceduralTexture::IsModified ) )    
        .def( 
            "IsValid"
            , (bool ( ::PyProceduralTexture::* )(  ))( &::PyProceduralTexture::IsValid ) )    
        .def( 
            "SetAllPixels"
            , (void ( ::PyProceduralTexture::* )( int ))( &::PyProceduralTexture::SetAllPixels )
            , ( bp::arg("i") ) )    
        .def( 
            "SetPixel"
            , (void ( ::PyProceduralTexture::* )( int,int,int ))( &::PyProceduralTexture::SetPixel )
            , ( bp::arg("x"), bp::arg("y"), bp::arg("i") ) )    
        .def( 
            "SetPixel"
            , (void ( ::PyProceduralTexture::* )( int,int,int,int,int,int ))( &::PyProceduralTexture::SetPixel )
            , ( bp::arg("x"), bp::arg("y"), bp::arg("r"), bp::arg("g"), bp::arg("b"), bp::arg("a") ) )    
        .def( 
            "SetPixel"
            , (void ( ::PyProceduralTexture::* )( int,int,::Color const & ))( &::PyProceduralTexture::SetPixel )
            , ( bp::arg("x"), bp::arg("y"), bp::arg("c") ) )    
        .def( 
            "Shutdown"
            , (void ( ::PyProceduralTexture::* )(  ))( &::PyProceduralTexture::Shutdown ) );
}
#else
#include "cbase.h"

#include "materialsystem/imaterial.h"

#include "materialsystem/MaterialSystemUtil.h"

#include "python/srcpy_materials.h"

#include "view_shared.h"

#include "tier0/valve_minmax_off.h"

#include "srcpy.h"

#include "tier0/valve_minmax_on.h"

#include "tier0/memdbgon.h"

namespace bp = boost::python;

BOOST_PYTHON_MODULE(materials){
    bp::docstring_options doc_options( true, true, false );

    { //::CMaterialReference
        typedef bp::class_< CMaterialReference > CMaterialReference_exposer_t;
        CMaterialReference_exposer_t CMaterialReference_exposer = CMaterialReference_exposer_t( "CMaterialReference", bp::init< bp::optional< char const *, char const *, bool > >(( bp::arg("pMaterialName")=bp::object(), bp::arg("pTextureGroupName")=bp::object(), bp::arg("bComplain")=(bool)(true) )) );
        bp::scope CMaterialReference_scope( CMaterialReference_exposer );
        bp::implicitly_convertible< char const *, CMaterialReference >();
        { //::CMaterialReference::Init
        
            typedef void ( ::CMaterialReference::*Init_function_type)( char const *,char const *,bool ) ;
            
            CMaterialReference_exposer.def( 
                "Init"
                , Init_function_type( &::CMaterialReference::Init )
                , ( bp::arg("pMaterialName"), bp::arg("pTextureGroupName"), bp::arg("bComplain")=(bool)(true) ) );
        
        }
        { //::CMaterialReference::Init
        
            typedef void ( ::CMaterialReference::*Init_function_type)( char const *,::KeyValues * ) ;
            
            CMaterialReference_exposer.def( 
                "Init"
                , Init_function_type( &::CMaterialReference::Init )
                , ( bp::arg("pMaterialName"), bp::arg("pVMTKeyValues") ) );
        
        }
        { //::CMaterialReference::Init
        
            typedef void ( ::CMaterialReference::*Init_function_type)( ::IMaterial * ) ;
            
            CMaterialReference_exposer.def( 
                "Init"
                , Init_function_type( &::CMaterialReference::Init )
                , ( bp::arg("pMaterial") ) );
        
        }
        { //::CMaterialReference::Init
        
            typedef void ( ::CMaterialReference::*Init_function_type)( ::CMaterialReference & ) ;
            
            CMaterialReference_exposer.def( 
                "Init"
                , Init_function_type( &::CMaterialReference::Init )
                , ( bp::arg("ref") ) );
        
        }
        { //::CMaterialReference::Init
        
            typedef void ( ::CMaterialReference::*Init_function_type)( char const *,char const *,::KeyValues * ) ;
            
            CMaterialReference_exposer.def( 
                "Init"
                , Init_function_type( &::CMaterialReference::Init )
                , ( bp::arg("pMaterialName"), bp::arg("pTextureGroupName"), bp::arg("pVMTKeyValues") ) );
        
        }
        { //::CMaterialReference::IsValid
        
            typedef bool ( ::CMaterialReference::*IsValid_function_type)(  ) ;
            
            CMaterialReference_exposer.def( 
                "IsValid"
                , IsValid_function_type( &::CMaterialReference::IsValid ) );
        
        }
        { //::CMaterialReference::Shutdown
        
            typedef void ( ::CMaterialReference::*Shutdown_function_type)(  ) ;
            
            CMaterialReference_exposer.def( 
                "Shutdown"
                , Shutdown_function_type( &::CMaterialReference::Shutdown ) );
        
        }
    }
}
#endif

