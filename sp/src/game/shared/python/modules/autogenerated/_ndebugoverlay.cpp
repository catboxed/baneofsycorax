// This file has been generated by Py++.

#include "cbase.h"
#ifdef CLIENT_DLL
#include "cbase.h"

#include "debugoverlay_shared.h"

#include "tier0/valve_minmax_off.h"

#include "srcpy.h"

#include "tier0/valve_minmax_on.h"

#include "tier0/memdbgon.h"

namespace bp = boost::python;

class CBaseEntity;

BOOST_PYTHON_MODULE(_ndebugoverlay){
    bp::docstring_options doc_options( true, true, false );

    { //::NDebugOverlay::Axis
    
        typedef void ( *Axis_function_type )( ::Vector const &,::QAngle const &,float,bool,float );
        
        bp::def( 
            "Axis"
            , Axis_function_type( &::NDebugOverlay::Axis )
            , ( bp::arg("position"), bp::arg("angles"), bp::arg("size"), bp::arg("noDepthTest"), bp::arg("flDuration") ) );
    
    }

    { //::NDebugOverlay::Box
    
        typedef void ( *Box_function_type )( ::Vector const &,::Vector const &,::Vector const &,int,int,int,int,float );
        
        bp::def( 
            "Box"
            , Box_function_type( &::NDebugOverlay::Box )
            , ( bp::arg("origin"), bp::arg("mins"), bp::arg("maxs"), bp::arg("r"), bp::arg("g"), bp::arg("b"), bp::arg("a"), bp::arg("flDuration") ) );
    
    }

    { //::NDebugOverlay::BoxAngles
    
        typedef void ( *BoxAngles_function_type )( ::Vector const &,::Vector const &,::Vector const &,::QAngle const &,int,int,int,int,float );
        
        bp::def( 
            "BoxAngles"
            , BoxAngles_function_type( &::NDebugOverlay::BoxAngles )
            , ( bp::arg("origin"), bp::arg("mins"), bp::arg("maxs"), bp::arg("angles"), bp::arg("r"), bp::arg("g"), bp::arg("b"), bp::arg("a"), bp::arg("flDuration") ) );
    
    }

    { //::NDebugOverlay::BoxDirection
    
        typedef void ( *BoxDirection_function_type )( ::Vector const &,::Vector const &,::Vector const &,::Vector const &,int,int,int,int,float );
        
        bp::def( 
            "BoxDirection"
            , BoxDirection_function_type( &::NDebugOverlay::BoxDirection )
            , ( bp::arg("origin"), bp::arg("mins"), bp::arg("maxs"), bp::arg("forward"), bp::arg("r"), bp::arg("g"), bp::arg("b"), bp::arg("a"), bp::arg("flDuration") ) );
    
    }

    { //::NDebugOverlay::Circle
    
        typedef void ( *Circle_function_type )( ::Vector const &,float,int,int,int,int,bool,float );
        
        bp::def( 
            "Circle"
            , Circle_function_type( &::NDebugOverlay::Circle )
            , ( bp::arg("position"), bp::arg("radius"), bp::arg("r"), bp::arg("g"), bp::arg("b"), bp::arg("a"), bp::arg("bNoDepthTest"), bp::arg("flDuration") ) );
    
    }

    { //::NDebugOverlay::Circle
    
        typedef void ( *Circle_function_type )( ::Vector const &,::QAngle const &,float,int,int,int,int,bool,float );
        
        bp::def( 
            "Circle"
            , Circle_function_type( &::NDebugOverlay::Circle )
            , ( bp::arg("position"), bp::arg("angles"), bp::arg("radius"), bp::arg("r"), bp::arg("g"), bp::arg("b"), bp::arg("a"), bp::arg("bNoDepthTest"), bp::arg("flDuration") ) );
    
    }

    { //::NDebugOverlay::Circle
    
        typedef void ( *Circle_function_type )( ::Vector const &,::Vector const &,::Vector const &,float,int,int,int,int,bool,float );
        
        bp::def( 
            "Circle"
            , Circle_function_type( &::NDebugOverlay::Circle )
            , ( bp::arg("position"), bp::arg("xAxis"), bp::arg("yAxis"), bp::arg("radius"), bp::arg("r"), bp::arg("g"), bp::arg("b"), bp::arg("a"), bp::arg("bNoDepthTest"), bp::arg("flDuration") ) );
    
    }

    { //::NDebugOverlay::Cross3D
    
        typedef void ( *Cross3D_function_type )( ::Vector const &,::Vector const &,::Vector const &,int,int,int,bool,float );
        
        bp::def( 
            "Cross3D"
            , Cross3D_function_type( &::NDebugOverlay::Cross3D )
            , ( bp::arg("position"), bp::arg("mins"), bp::arg("maxs"), bp::arg("r"), bp::arg("g"), bp::arg("b"), bp::arg("noDepthTest"), bp::arg("flDuration") ) );
    
    }

    { //::NDebugOverlay::Cross3D
    
        typedef void ( *Cross3D_function_type )( ::Vector const &,float,int,int,int,bool,float );
        
        bp::def( 
            "Cross3D"
            , Cross3D_function_type( &::NDebugOverlay::Cross3D )
            , ( bp::arg("position"), bp::arg("size"), bp::arg("r"), bp::arg("g"), bp::arg("b"), bp::arg("noDepthTest"), bp::arg("flDuration") ) );
    
    }

    { //::NDebugOverlay::Cross3DOriented
    
        typedef void ( *Cross3DOriented_function_type )( ::Vector const &,::QAngle const &,float,int,int,int,bool,float );
        
        bp::def( 
            "Cross3DOriented"
            , Cross3DOriented_function_type( &::NDebugOverlay::Cross3DOriented )
            , ( bp::arg("position"), bp::arg("angles"), bp::arg("size"), bp::arg("r"), bp::arg("g"), bp::arg("b"), bp::arg("noDepthTest"), bp::arg("flDuration") ) );
    
    }

    { //::NDebugOverlay::Cross3DOriented
    
        typedef void ( *Cross3DOriented_function_type )( ::matrix3x4_t const &,float,int,bool,float );
        
        bp::def( 
            "Cross3DOriented"
            , Cross3DOriented_function_type( &::NDebugOverlay::Cross3DOriented )
            , ( bp::arg("m"), bp::arg("size"), bp::arg("c"), bp::arg("noDepthTest"), bp::arg("flDuration") ) );
    
    }

    { //::NDebugOverlay::DrawGroundCrossHairOverlay
    
        typedef void ( *DrawGroundCrossHairOverlay_function_type )(  );
        
        bp::def( 
            "DrawGroundCrossHairOverlay"
            , DrawGroundCrossHairOverlay_function_type( &::NDebugOverlay::DrawGroundCrossHairOverlay ) );
    
    }

    { //::NDebugOverlay::DrawTickMarkedLine
    
        typedef void ( *DrawTickMarkedLine_function_type )( ::Vector const &,::Vector const &,float,int,int,int,int,bool,float );
        
        bp::def( 
            "DrawTickMarkedLine"
            , DrawTickMarkedLine_function_type( &::NDebugOverlay::DrawTickMarkedLine )
            , ( bp::arg("startPos"), bp::arg("endPos"), bp::arg("tickDist"), bp::arg("tickTextDist"), bp::arg("r"), bp::arg("g"), bp::arg("b"), bp::arg("noDepthTest"), bp::arg("flDuration") ) );
    
    }

    { //::NDebugOverlay::EntityBounds
    
        typedef void ( *EntityBounds_function_type )( ::C_BaseEntity const *,int,int,int,int,float );
        
        bp::def( 
            "EntityBounds"
            , EntityBounds_function_type( &::NDebugOverlay::EntityBounds )
            , ( bp::arg("pEntity"), bp::arg("r"), bp::arg("g"), bp::arg("b"), bp::arg("a"), bp::arg("flDuration") ) );
    
    }

    { //::NDebugOverlay::EntityText
    
        typedef void ( *EntityText_function_type )( int,int,char const *,float,int,int,int,int );
        
        bp::def( 
            "EntityText"
            , EntityText_function_type( &::NDebugOverlay::EntityText )
            , ( bp::arg("entityID"), bp::arg("text_offset"), bp::arg("text"), bp::arg("flDuration"), bp::arg("r")=(int)(255), bp::arg("g")=(int)(255), bp::arg("b")=(int)(255), bp::arg("a")=(int)(255) ) );
    
    }

    { //::NDebugOverlay::EntityTextAtPosition
    
        typedef void ( *EntityTextAtPosition_function_type )( ::Vector const &,int,char const *,float,int,int,int,int );
        
        bp::def( 
            "EntityTextAtPosition"
            , EntityTextAtPosition_function_type( &::NDebugOverlay::EntityTextAtPosition )
            , ( bp::arg("origin"), bp::arg("text_offset"), bp::arg("text"), bp::arg("flDuration"), bp::arg("r")=(int)(255), bp::arg("g")=(int)(255), bp::arg("b")=(int)(255), bp::arg("a")=(int)(255) ) );
    
    }

    { //::NDebugOverlay::Grid
    
        typedef void ( *Grid_function_type )( ::Vector const & );
        
        bp::def( 
            "Grid"
            , Grid_function_type( &::NDebugOverlay::Grid )
            , ( bp::arg("vPosition") ) );
    
    }

    { //::NDebugOverlay::HorzArrow
    
        typedef void ( *HorzArrow_function_type )( ::Vector const &,::Vector const &,float,int,int,int,int,bool,float );
        
        bp::def( 
            "HorzArrow"
            , HorzArrow_function_type( &::NDebugOverlay::HorzArrow )
            , ( bp::arg("startPos"), bp::arg("endPos"), bp::arg("width"), bp::arg("r"), bp::arg("g"), bp::arg("b"), bp::arg("a"), bp::arg("noDepthTest"), bp::arg("flDuration") ) );
    
    }

    { //::NDebugOverlay::Line
    
        typedef void ( *Line_function_type )( ::Vector const &,::Vector const &,int,int,int,bool,float );
        
        bp::def( 
            "Line"
            , Line_function_type( &::NDebugOverlay::Line )
            , ( bp::arg("origin"), bp::arg("target"), bp::arg("r"), bp::arg("g"), bp::arg("b"), bp::arg("noDepthTest"), bp::arg("flDuration") ) );
    
    }

    { //::NDebugOverlay::ScreenText
    
        typedef void ( *ScreenText_function_type )( float,float,char const *,int,int,int,int,float );
        
        bp::def( 
            "ScreenText"
            , ScreenText_function_type( &::NDebugOverlay::ScreenText )
            , ( bp::arg("fXpos"), bp::arg("fYpos"), bp::arg("text"), bp::arg("r"), bp::arg("g"), bp::arg("b"), bp::arg("a"), bp::arg("flDuration") ) );
    
    }

    { //::NDebugOverlay::Sphere
    
        typedef void ( *Sphere_function_type )( ::Vector const &,float,int,int,int,bool,float );
        
        bp::def( 
            "Sphere"
            , Sphere_function_type( &::NDebugOverlay::Sphere )
            , ( bp::arg("center"), bp::arg("radius"), bp::arg("r"), bp::arg("g"), bp::arg("b"), bp::arg("noDepthTest"), bp::arg("flDuration") ) );
    
    }

    { //::NDebugOverlay::Sphere
    
        typedef void ( *Sphere_function_type )( ::Vector const &,::QAngle const &,float,int,int,int,int,bool,float );
        
        bp::def( 
            "Sphere"
            , Sphere_function_type( &::NDebugOverlay::Sphere )
            , ( bp::arg("position"), bp::arg("angles"), bp::arg("radius"), bp::arg("r"), bp::arg("g"), bp::arg("b"), bp::arg("a"), bp::arg("bNoDepthTest"), bp::arg("flDuration") ) );
    
    }

    { //::NDebugOverlay::SweptBox
    
        typedef void ( *SweptBox_function_type )( ::Vector const &,::Vector const &,::Vector const &,::Vector const &,::QAngle const &,int,int,int,int,float );
        
        bp::def( 
            "SweptBox"
            , SweptBox_function_type( &::NDebugOverlay::SweptBox )
            , ( bp::arg("start"), bp::arg("end"), bp::arg("mins"), bp::arg("maxs"), bp::arg("angles"), bp::arg("r"), bp::arg("g"), bp::arg("b"), bp::arg("a"), bp::arg("flDuration") ) );
    
    }

    { //::NDebugOverlay::Text
    
        typedef void ( *Text_function_type )( ::Vector const &,char const *,bool,float );
        
        bp::def( 
            "Text"
            , Text_function_type( &::NDebugOverlay::Text )
            , ( bp::arg("origin"), bp::arg("text"), bp::arg("bViewCheck"), bp::arg("flDuration") ) );
    
    }

    { //::NDebugOverlay::Triangle
    
        typedef void ( *Triangle_function_type )( ::Vector const &,::Vector const &,::Vector const &,int,int,int,int,bool,float );
        
        bp::def( 
            "Triangle"
            , Triangle_function_type( &::NDebugOverlay::Triangle )
            , ( bp::arg("p1"), bp::arg("p2"), bp::arg("p3"), bp::arg("r"), bp::arg("g"), bp::arg("b"), bp::arg("a"), bp::arg("noDepthTest"), bp::arg("duration") ) );
    
    }

    { //::NDebugOverlay::VertArrow
    
        typedef void ( *VertArrow_function_type )( ::Vector const &,::Vector const &,float,int,int,int,int,bool,float );
        
        bp::def( 
            "VertArrow"
            , VertArrow_function_type( &::NDebugOverlay::VertArrow )
            , ( bp::arg("startPos"), bp::arg("endPos"), bp::arg("width"), bp::arg("r"), bp::arg("g"), bp::arg("b"), bp::arg("a"), bp::arg("noDepthTest"), bp::arg("flDuration") ) );
    
    }

    { //::NDebugOverlay::YawArrow
    
        typedef void ( *YawArrow_function_type )( ::Vector const &,float,float,float,int,int,int,int,bool,float );
        
        bp::def( 
            "YawArrow"
            , YawArrow_function_type( &::NDebugOverlay::YawArrow )
            , ( bp::arg("startPos"), bp::arg("yaw"), bp::arg("length"), bp::arg("width"), bp::arg("r"), bp::arg("g"), bp::arg("b"), bp::arg("a"), bp::arg("noDepthTest"), bp::arg("flDuration") ) );
    
    }
}
#else
#include "cbase.h"

#include "debugoverlay_shared.h"

#include "tier0/valve_minmax_off.h"

#include "srcpy.h"

#include "tier0/valve_minmax_on.h"

#include "tier0/memdbgon.h"

namespace bp = boost::python;

class CBaseEntity;

BOOST_PYTHON_MODULE(_ndebugoverlay){
    bp::docstring_options doc_options( true, true, false );

    { //::NDebugOverlay::Axis
    
        typedef void ( *Axis_function_type )( ::Vector const &,::QAngle const &,float,bool,float );
        
        bp::def( 
            "Axis"
            , Axis_function_type( &::NDebugOverlay::Axis )
            , ( bp::arg("position"), bp::arg("angles"), bp::arg("size"), bp::arg("noDepthTest"), bp::arg("flDuration") ) );
    
    }

    { //::NDebugOverlay::Box
    
        typedef void ( *Box_function_type )( ::Vector const &,::Vector const &,::Vector const &,int,int,int,int,float );
        
        bp::def( 
            "Box"
            , Box_function_type( &::NDebugOverlay::Box )
            , ( bp::arg("origin"), bp::arg("mins"), bp::arg("maxs"), bp::arg("r"), bp::arg("g"), bp::arg("b"), bp::arg("a"), bp::arg("flDuration") ) );
    
    }

    { //::NDebugOverlay::BoxAngles
    
        typedef void ( *BoxAngles_function_type )( ::Vector const &,::Vector const &,::Vector const &,::QAngle const &,int,int,int,int,float );
        
        bp::def( 
            "BoxAngles"
            , BoxAngles_function_type( &::NDebugOverlay::BoxAngles )
            , ( bp::arg("origin"), bp::arg("mins"), bp::arg("maxs"), bp::arg("angles"), bp::arg("r"), bp::arg("g"), bp::arg("b"), bp::arg("a"), bp::arg("flDuration") ) );
    
    }

    { //::NDebugOverlay::BoxDirection
    
        typedef void ( *BoxDirection_function_type )( ::Vector const &,::Vector const &,::Vector const &,::Vector const &,int,int,int,int,float );
        
        bp::def( 
            "BoxDirection"
            , BoxDirection_function_type( &::NDebugOverlay::BoxDirection )
            , ( bp::arg("origin"), bp::arg("mins"), bp::arg("maxs"), bp::arg("forward"), bp::arg("r"), bp::arg("g"), bp::arg("b"), bp::arg("a"), bp::arg("flDuration") ) );
    
    }

    { //::NDebugOverlay::Circle
    
        typedef void ( *Circle_function_type )( ::Vector const &,float,int,int,int,int,bool,float );
        
        bp::def( 
            "Circle"
            , Circle_function_type( &::NDebugOverlay::Circle )
            , ( bp::arg("position"), bp::arg("radius"), bp::arg("r"), bp::arg("g"), bp::arg("b"), bp::arg("a"), bp::arg("bNoDepthTest"), bp::arg("flDuration") ) );
    
    }

    { //::NDebugOverlay::Circle
    
        typedef void ( *Circle_function_type )( ::Vector const &,::QAngle const &,float,int,int,int,int,bool,float );
        
        bp::def( 
            "Circle"
            , Circle_function_type( &::NDebugOverlay::Circle )
            , ( bp::arg("position"), bp::arg("angles"), bp::arg("radius"), bp::arg("r"), bp::arg("g"), bp::arg("b"), bp::arg("a"), bp::arg("bNoDepthTest"), bp::arg("flDuration") ) );
    
    }

    { //::NDebugOverlay::Circle
    
        typedef void ( *Circle_function_type )( ::Vector const &,::Vector const &,::Vector const &,float,int,int,int,int,bool,float );
        
        bp::def( 
            "Circle"
            , Circle_function_type( &::NDebugOverlay::Circle )
            , ( bp::arg("position"), bp::arg("xAxis"), bp::arg("yAxis"), bp::arg("radius"), bp::arg("r"), bp::arg("g"), bp::arg("b"), bp::arg("a"), bp::arg("bNoDepthTest"), bp::arg("flDuration") ) );
    
    }

    { //::NDebugOverlay::Cross3D
    
        typedef void ( *Cross3D_function_type )( ::Vector const &,::Vector const &,::Vector const &,int,int,int,bool,float );
        
        bp::def( 
            "Cross3D"
            , Cross3D_function_type( &::NDebugOverlay::Cross3D )
            , ( bp::arg("position"), bp::arg("mins"), bp::arg("maxs"), bp::arg("r"), bp::arg("g"), bp::arg("b"), bp::arg("noDepthTest"), bp::arg("flDuration") ) );
    
    }

    { //::NDebugOverlay::Cross3D
    
        typedef void ( *Cross3D_function_type )( ::Vector const &,float,int,int,int,bool,float );
        
        bp::def( 
            "Cross3D"
            , Cross3D_function_type( &::NDebugOverlay::Cross3D )
            , ( bp::arg("position"), bp::arg("size"), bp::arg("r"), bp::arg("g"), bp::arg("b"), bp::arg("noDepthTest"), bp::arg("flDuration") ) );
    
    }

    { //::NDebugOverlay::Cross3DOriented
    
        typedef void ( *Cross3DOriented_function_type )( ::Vector const &,::QAngle const &,float,int,int,int,bool,float );
        
        bp::def( 
            "Cross3DOriented"
            , Cross3DOriented_function_type( &::NDebugOverlay::Cross3DOriented )
            , ( bp::arg("position"), bp::arg("angles"), bp::arg("size"), bp::arg("r"), bp::arg("g"), bp::arg("b"), bp::arg("noDepthTest"), bp::arg("flDuration") ) );
    
    }

    { //::NDebugOverlay::Cross3DOriented
    
        typedef void ( *Cross3DOriented_function_type )( ::matrix3x4_t const &,float,int,bool,float );
        
        bp::def( 
            "Cross3DOriented"
            , Cross3DOriented_function_type( &::NDebugOverlay::Cross3DOriented )
            , ( bp::arg("m"), bp::arg("size"), bp::arg("c"), bp::arg("noDepthTest"), bp::arg("flDuration") ) );
    
    }

    { //::NDebugOverlay::DrawGroundCrossHairOverlay
    
        typedef void ( *DrawGroundCrossHairOverlay_function_type )(  );
        
        bp::def( 
            "DrawGroundCrossHairOverlay"
            , DrawGroundCrossHairOverlay_function_type( &::NDebugOverlay::DrawGroundCrossHairOverlay ) );
    
    }

    { //::NDebugOverlay::DrawTickMarkedLine
    
        typedef void ( *DrawTickMarkedLine_function_type )( ::Vector const &,::Vector const &,float,int,int,int,int,bool,float );
        
        bp::def( 
            "DrawTickMarkedLine"
            , DrawTickMarkedLine_function_type( &::NDebugOverlay::DrawTickMarkedLine )
            , ( bp::arg("startPos"), bp::arg("endPos"), bp::arg("tickDist"), bp::arg("tickTextDist"), bp::arg("r"), bp::arg("g"), bp::arg("b"), bp::arg("noDepthTest"), bp::arg("flDuration") ) );
    
    }

    { //::NDebugOverlay::EntityBounds
    
        typedef void ( *EntityBounds_function_type )( ::CBaseEntity const *,int,int,int,int,float );
        
        bp::def( 
            "EntityBounds"
            , EntityBounds_function_type( &::NDebugOverlay::EntityBounds )
            , ( bp::arg("pEntity"), bp::arg("r"), bp::arg("g"), bp::arg("b"), bp::arg("a"), bp::arg("flDuration") ) );
    
    }

    { //::NDebugOverlay::EntityText
    
        typedef void ( *EntityText_function_type )( int,int,char const *,float,int,int,int,int );
        
        bp::def( 
            "EntityText"
            , EntityText_function_type( &::NDebugOverlay::EntityText )
            , ( bp::arg("entityID"), bp::arg("text_offset"), bp::arg("text"), bp::arg("flDuration"), bp::arg("r")=(int)(255), bp::arg("g")=(int)(255), bp::arg("b")=(int)(255), bp::arg("a")=(int)(255) ) );
    
    }

    { //::NDebugOverlay::EntityTextAtPosition
    
        typedef void ( *EntityTextAtPosition_function_type )( ::Vector const &,int,char const *,float,int,int,int,int );
        
        bp::def( 
            "EntityTextAtPosition"
            , EntityTextAtPosition_function_type( &::NDebugOverlay::EntityTextAtPosition )
            , ( bp::arg("origin"), bp::arg("text_offset"), bp::arg("text"), bp::arg("flDuration"), bp::arg("r")=(int)(255), bp::arg("g")=(int)(255), bp::arg("b")=(int)(255), bp::arg("a")=(int)(255) ) );
    
    }

    { //::NDebugOverlay::Grid
    
        typedef void ( *Grid_function_type )( ::Vector const & );
        
        bp::def( 
            "Grid"
            , Grid_function_type( &::NDebugOverlay::Grid )
            , ( bp::arg("vPosition") ) );
    
    }

    { //::NDebugOverlay::HorzArrow
    
        typedef void ( *HorzArrow_function_type )( ::Vector const &,::Vector const &,float,int,int,int,int,bool,float );
        
        bp::def( 
            "HorzArrow"
            , HorzArrow_function_type( &::NDebugOverlay::HorzArrow )
            , ( bp::arg("startPos"), bp::arg("endPos"), bp::arg("width"), bp::arg("r"), bp::arg("g"), bp::arg("b"), bp::arg("a"), bp::arg("noDepthTest"), bp::arg("flDuration") ) );
    
    }

    { //::NDebugOverlay::Line
    
        typedef void ( *Line_function_type )( ::Vector const &,::Vector const &,int,int,int,bool,float );
        
        bp::def( 
            "Line"
            , Line_function_type( &::NDebugOverlay::Line )
            , ( bp::arg("origin"), bp::arg("target"), bp::arg("r"), bp::arg("g"), bp::arg("b"), bp::arg("noDepthTest"), bp::arg("flDuration") ) );
    
    }

    { //::NDebugOverlay::ScreenText
    
        typedef void ( *ScreenText_function_type )( float,float,char const *,int,int,int,int,float );
        
        bp::def( 
            "ScreenText"
            , ScreenText_function_type( &::NDebugOverlay::ScreenText )
            , ( bp::arg("fXpos"), bp::arg("fYpos"), bp::arg("text"), bp::arg("r"), bp::arg("g"), bp::arg("b"), bp::arg("a"), bp::arg("flDuration") ) );
    
    }

    { //::NDebugOverlay::Sphere
    
        typedef void ( *Sphere_function_type )( ::Vector const &,float,int,int,int,bool,float );
        
        bp::def( 
            "Sphere"
            , Sphere_function_type( &::NDebugOverlay::Sphere )
            , ( bp::arg("center"), bp::arg("radius"), bp::arg("r"), bp::arg("g"), bp::arg("b"), bp::arg("noDepthTest"), bp::arg("flDuration") ) );
    
    }

    { //::NDebugOverlay::Sphere
    
        typedef void ( *Sphere_function_type )( ::Vector const &,::QAngle const &,float,int,int,int,int,bool,float );
        
        bp::def( 
            "Sphere"
            , Sphere_function_type( &::NDebugOverlay::Sphere )
            , ( bp::arg("position"), bp::arg("angles"), bp::arg("radius"), bp::arg("r"), bp::arg("g"), bp::arg("b"), bp::arg("a"), bp::arg("bNoDepthTest"), bp::arg("flDuration") ) );
    
    }

    { //::NDebugOverlay::SweptBox
    
        typedef void ( *SweptBox_function_type )( ::Vector const &,::Vector const &,::Vector const &,::Vector const &,::QAngle const &,int,int,int,int,float );
        
        bp::def( 
            "SweptBox"
            , SweptBox_function_type( &::NDebugOverlay::SweptBox )
            , ( bp::arg("start"), bp::arg("end"), bp::arg("mins"), bp::arg("maxs"), bp::arg("angles"), bp::arg("r"), bp::arg("g"), bp::arg("b"), bp::arg("a"), bp::arg("flDuration") ) );
    
    }

    { //::NDebugOverlay::Text
    
        typedef void ( *Text_function_type )( ::Vector const &,char const *,bool,float );
        
        bp::def( 
            "Text"
            , Text_function_type( &::NDebugOverlay::Text )
            , ( bp::arg("origin"), bp::arg("text"), bp::arg("bViewCheck"), bp::arg("flDuration") ) );
    
    }

    { //::NDebugOverlay::Triangle
    
        typedef void ( *Triangle_function_type )( ::Vector const &,::Vector const &,::Vector const &,int,int,int,int,bool,float );
        
        bp::def( 
            "Triangle"
            , Triangle_function_type( &::NDebugOverlay::Triangle )
            , ( bp::arg("p1"), bp::arg("p2"), bp::arg("p3"), bp::arg("r"), bp::arg("g"), bp::arg("b"), bp::arg("a"), bp::arg("noDepthTest"), bp::arg("duration") ) );
    
    }

    { //::NDebugOverlay::VertArrow
    
        typedef void ( *VertArrow_function_type )( ::Vector const &,::Vector const &,float,int,int,int,int,bool,float );
        
        bp::def( 
            "VertArrow"
            , VertArrow_function_type( &::NDebugOverlay::VertArrow )
            , ( bp::arg("startPos"), bp::arg("endPos"), bp::arg("width"), bp::arg("r"), bp::arg("g"), bp::arg("b"), bp::arg("a"), bp::arg("noDepthTest"), bp::arg("flDuration") ) );
    
    }

    { //::NDebugOverlay::YawArrow
    
        typedef void ( *YawArrow_function_type )( ::Vector const &,float,float,float,int,int,int,int,bool,float );
        
        bp::def( 
            "YawArrow"
            , YawArrow_function_type( &::NDebugOverlay::YawArrow )
            , ( bp::arg("startPos"), bp::arg("yaw"), bp::arg("length"), bp::arg("width"), bp::arg("r"), bp::arg("g"), bp::arg("b"), bp::arg("a"), bp::arg("noDepthTest"), bp::arg("flDuration") ) );
    
    }
}
#endif

