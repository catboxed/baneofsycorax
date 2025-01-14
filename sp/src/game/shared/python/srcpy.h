//====== Copyright © Sandern Corporation, All rights reserved. ===========//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef SRCPY_H
#define SRCPY_H
#ifdef _WIN32
#pragma once
#endif

#ifndef ENABLE_PYTHON
#error "Python is disabled. Do not include this!"
#endif // ENABLE_PYTHON

#include "srcpy_boostpython.h"

extern ConVar g_debug_python;
#define DbgStrPyMsg if ( !g_debug_python.GetBool() ) ; else DevMsg

extern const Color g_PythonColor;

// The thread ID in which python is initialized
// This is for debugging, we should only make calls to python in this thread
// If we want to support calling from multiple threads we must lock the GIL before calling
extern unsigned int g_hPythonThreadID;

#ifndef _DEBUG

/* Undef this to remove the thread id checks */
//#define PY_CHECKTHREADID

/* Define this to check if we should log overrides calls */
//#define PY_CHECK_LOG_OVERRIDES

#endif // _DEBUG

#if defined (PY_CHECK_LOG_OVERRIDES) || defined (_DEBUG)
	extern ConVar py_log_overrides;
	extern ConVar py_log_overrides_module;
#endif

// PY_CHECKTHREADID verifies a overridable Python method is not called from a different thread
// This would require setting up Python in a thread safe way (slower!)
#ifdef WIN32
#if defined(PY_CHECKTHREADID) && !defined(_DEBUG)
#define PY_OVERRIDE_CHECK( clsname, methodname ) \
    if( GetCurrentThreadId() != g_hPythonThreadID ) \
	Error( #methodname ": Client? %d. Thread ID is not the same as in which the python interpreter is initialized! %d != %d.\n", CBaseEntity::IsClient(), g_hPythonThreadID, GetCurrentThreadId() );
#else
#define PY_OVERRIDE_CHECK( clsname, methodname ) \
    Assert( SrcPySystem()->IsPythonRunning() ); \
    Assert( GetCurrentThreadId() == g_hPythonThreadID );
#endif
#else
#define PY_OVERRIDE_CHECK( clsname, methodname ) // empty
#endif // WIN32

// PY_OVERRIDE_LOG logs all method calls
#if defined(_DEBUG) || defined(PY_CHECK_LOG_OVERRIDES)
#define PY_OVERRIDE_LOG( modulename, clsname, methodname ) \
	if( py_log_overrides.GetBool() && (V_strlen(py_log_overrides_module.GetString()) == 0 || V_strcmp( py_log_overrides_module.GetString(), #modulename ) == 0 ) ) \
		Msg( #modulename ": Calling " #methodname "(  ) of Class \"" #clsname "\"\n" );
#else
#define PY_OVERRIDE_LOG( modulename, clsname, methodname ) // empty
#endif

#if defined(SRCPY_MOD_ENTITIES)
//-----------------------------------------------------------------------------
// Helper for converting IHandleEntity arguments to bp objects
//-----------------------------------------------------------------------------
inline boost::python::object PyEntityFromEntityHandle( IHandleEntity *pHandleEntity )
{
	CBaseEntity *pEnt = EntityFromEntityHandle( pHandleEntity );
	return pEnt ? pEnt->GetPyHandle() : boost::python::object();
}
#endif // SRCPY_MOD_ENTITIES

//-----------------------------------------------------------------------------
// Global variables to some commonly used modules. This way you don't need to import
// these modules, which saves time
//-----------------------------------------------------------------------------
extern boost::python::object mainmodule;
extern boost::python::object mainnamespace;

extern boost::python::object builtins;
extern boost::python::object types;
extern boost::python::object sys;
extern boost::python::object collections;
extern boost::python::object srcbuiltins;
extern boost::python::object steam;
extern boost::python::object _entitiesmisc;
extern boost::python::object _entities;
extern boost::python::object _particles;
extern boost::python::object _physics;

#ifdef CLIENT_DLL
	extern boost::python::object _vguicontrols;
#endif // CLIENT_DLL

extern boost::python::object fntype;
extern boost::python::object fnisinstance;

//-----------------------------------------------------------------------------
// Purpose: Adding modules to python
//-----------------------------------------------------------------------------
#define STRINGIZE(x) #x 
#define XSTR(x) STRINGIZE(x)

#if PY_VERSION_HEX < 0x03000000
#define PYINIT(x) init##x
#define PYINIT_DECL(x) void init##x
#else
#define PYINIT(x) PyInit_##x
#define PYINIT_DECL(x) PyObject* PyInit_##x
#endif // 0x03000000

#define APPEND_MODULE( x )											\
	if (PyImport_AppendInittab(STRINGIZE(x), PYINIT(x)) == -1)		\
{																	\
	Warning("[Python]Failed to init " #x " module\n");				\
}																	\

//-----------------------------------------------------------------------------
// Purpose: Two versions of PYGETVALUE. One prints the errors, the other doesn't
//-----------------------------------------------------------------------------
#define PYGETVALUE( attr_name, obj, T, def_value )												\
	if( obj.ptr() == Py_None )																	\
		return def_value;																		\
	if( hasattr(obj, attr_name) )																\
	{																							\
		try {																					\
			return boost::python::extract<T>(obj.attr(attr_name) );								\
		} catch(boost::python::error_already_set &) {											\
			PyErr_Clear();																		\
		}																						\
	}																							\
	else																						\
	{																							\
		PyErr_Clear();																			\
	}																							\
	return def_value;																			\

#define PYGETVALUE_ERR( attr_name, obj, T, def_value )											\
	if( obj.ptr() == Py_None )																	\
		return def_value;																		\
	if( hasattr(obj, attr_name) )																\
	{																							\
		try {																					\
			return boost::python::extract<T>(obj.attr(attr_name) );								\
		} catch(boost::python::error_already_set &) {											\
			PyErr_Print();																		\
			PyErr_Clear();																		\
		}																						\
	}																							\
	else																						\
	{																							\
		PyErr_Print();																			\
	}																							\
	return def_value;																			\

inline bool hasattr(boost::python::object obj, const char *attrName) {
	return PyObject_HasAttrString(obj.ptr(), attrName);
}

//-----------------------------------------------------------------------------
// Purpose: Running a method
//			For comfort reason we check if the method is None and just return
//			then. If it is important to know the method object is none, then that 
//			should be done while retrieving the object.
//			This is done because a method might or might not be implemented in 
//			python.
//-----------------------------------------------------------------------------
#define PYRUNMETHOD( method, report_errors, ... )												\
	if( method.ptr() == Py_None )																\
		return;																					\
	try	{																						\
		method(__VA_ARGS__);																	\
	} catch(boost::python::error_already_set &)	{												\
		if( report_errors )																		\
			PyErr_Print();																		\
		else																					\
			PyErr_Clear();																		\
	}																							\

#define PYRUNMETHOD_RV( method, T, def_value, report_errors, ... )								\
	if( method.ptr() == Py_None )																\
		return def_value;																		\
	try	{																						\
		return boost::python::extract<T>(method(__VA_ARGS__));									\
	} catch(boost::python::error_already_set &) {												\
		if( report_errors )																		\
			PyErr_Print();																		\
		else																					\
			PyErr_Clear();																		\
	}																							\
	return def_value;																			\

template< class T >
boost::python::list UtlVectorToListByValue( CUtlVector<T> & vec )
{
	boost::python::list l;
	for( int i = 0; i < vec.Count(); i++ )
		l.append( *vec[i] );
	return l;
}

template< class T >
void ListToUtlVectorByValue( boost::python::list listIn, CUtlVector<T> & outVec )
{
	int n = boost::python::len(listIn);
	for( int i = 0; i < n; i++ )
		outVec.AddToTail( boost::python::extract<T>( listIn[i] ) );
}


//-----------------------------------------------------------------------------
// Purpose: Python classes should not register entities before level init
//			To prevent double calls.
//-----------------------------------------------------------------------------
extern bool g_bDoNotInitPythonClasses;

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
class CSrcPython : public CBaseGameSystemPerFrame
{
public:
	CSrcPython();
	virtual const char		*Name( void ) { return "CSrcPython"; }

	virtual bool			Init( void );
	virtual void			Shutdown( void );
	virtual void			ExtraShutdown( void ); // Shutdown is called before shutting down vgui. This one is after that.
	virtual void			PostInit();
	virtual void			LevelInitPreEntity();
	virtual void			LevelInitPostEntity();
	virtual void			LevelShutdownPreEntity();
	virtual void			LevelShutdownPostEntity();

	bool					InitInterpreter( void );
	bool					PostInitInterpreter( bool bStandAloneInterpreter = false );
	bool					PreShutdownInterpreter( bool bStandAloneInterpreter = false );
	bool					PostShutdownInterpreter( bool bStandAloneInterpreter = false );
	bool					ShutdownInterpreter( void );
	void					PostInitInterpreterActions( void );

	// Initialize function for stand alone interpreter (from a separate executable, for dev'ing)
	virtual bool			InitStandAloneInterpreter();

	bool					IsPythonRunning();
	bool					IsPythonFinalizing(); // Special case
	bool					IsPathProtected(); // For file writing

#ifdef WIN32
	// Visual Studio Python Tools support
	bool					CheckVSPTDebugger();
#endif // WIN32

#ifdef CLIENT_DLL
	// Gets called each frame
	virtual void Update( float frametime );
#else
	virtual void FrameUpdatePostEntityThink( void );
#endif // CLIENT_DLL

public:
	boost::python::object	Import( const char *pModule );
	boost::python::object	ImportSilent( const char *pModule );
	boost::python::object	Get( const char *pAttrName, boost::python::object obj, bool bReport = false );
	boost::python::object	Get( const char *pAttrName, const char *pModule, bool bReport = false );
	void					Run( boost::python::object method, bool report_errors = true );
	void					Run( const char *pString, const char *pModule );
	void					Run( const char *pString, boost::python::object module = boost::python::object() );
	bool					ExecuteFile( const char* pScript );
	void					Reload( const char *pModule );
	void					GarbageCollect();
	void					SysAppendPath( const char* path, bool inclsubdirs = false );
	boost::python::object	CreateWeakRef( boost::python::object obj_ref );

	void					CallSignalNoArgs( boost::python::object signal );
	void					CallSignal( boost::python::object signal, boost::python::dict kwargs );

public:
	// Get Template
	template< class T >
	T Get( const char *name, boost::python::object obj, T default_value, bool report_errors = false )
	{
		if( report_errors ) {
			PYGETVALUE_ERR(name, obj, T, default_value);
		}
		else {
			PYGETVALUE(name, obj, T, default_value);
		}
	}

	// Getters
	int				GetInt(const char *name, const char *module, int default_value = 0, bool report_error = false );
	float			GetFloat(const char *name, const char *module, float default_value = 0.0f, bool report_error = false );
	const char		*GetString( const char *name, const char *module_name, const char *default_value = NULL, bool report_error = false);
	Vector			GetVector( const char *name, const char *module_name, Vector default_value = Vector(0, 0, 0), bool report_error = false);

	int				GetInt(const char *name, boost::python::object obj, int default_value = 0, bool report_error = false );
	float			GetFloat(const char *name, boost::python::object obj, float default_value = 0.0f, bool report_error = false );
	const char		*GetString( const char *name, boost::python::object obj, const char *default_value = NULL, bool report_error = false);
	Vector			GetVector( const char *name, boost::python::object obj, Vector default_value = Vector(0, 0, 0), bool report_error = false);

	// Namespace
	boost::python::object GetMainNameSpace() { return mainnamespace; } 		

public:
	// RUN TEMPLATES
	template<class A1>
	void Run( boost::python::object method, A1 arg1, bool report_errors = true )
	{
		PYRUNMETHOD( method, report_errors, arg1 )
	}

	template<class A1, class A2>
	void Run( boost::python::object method, A1 arg1, A2 arg2, bool report_errors = true  )
	{
		PYRUNMETHOD( method, report_errors, arg1, arg2 )
	}

	template<class A1, class A2, class A3 >
	void Run( boost::python::object method, A1 arg1, A2 arg2, A3 arg3, bool report_errors = true )
	{
		PYRUNMETHOD( method, report_errors, arg1, arg2, arg3 )
	}

	template<class A1, class A2, class A3, class A4>
	void Run( boost::python::object method, A1 arg1, A2 arg2, A3 arg3, A4 arg4, bool report_errors = true )
	{
		PYRUNMETHOD(method, report_errors, arg1, arg2, arg3, arg4);
	}

	template<class A1, class A2, class A3, class A4, class A5>
	void Run( boost::python::object method, A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5, bool report_errors = true  )
	{
		PYRUNMETHOD(method, report_errors, arg1, arg2, arg3, arg4, arg5);
	}

	template<class T>
	T RunT( boost::python::object method, T default_value, bool report_errors = true  )
	{
		PYRUNMETHOD_RV(method, T, default_value, report_errors);
	}

	template<class T, class A1>
	T RunT( boost::python::object method, T default_value, A1 arg1, bool report_errors = true  )
	{
		PYRUNMETHOD_RV(method, T, default_value, report_errors, arg1);
	}

	template<class T, class A1, class A2>
	T RunT( boost::python::object method, T default_value, A1 arg1, A2 arg2, bool report_errors = true  )
	{
		PYRUNMETHOD_RV(method, T, default_value, report_errors, arg1, arg2);
	}

	template<class T, class A1, class A2, class A3>
	T RunT( boost::python::object method, T default_value, A1 arg1, A2 arg2, A3 arg3, bool report_errors = true  )
	{
		PYRUNMETHOD_RV(method, T, default_value, report_errors, arg1, arg2, arg3 );
	}

	template<class T, class A1, class A2, class A3, class A4>
	T RunT( boost::python::object method, T default_value, A1 arg1, A2 arg2, A3 arg3, A4 arg4, bool report_errors = true  )
	{
		PYRUNMETHOD_RV(method, T, default_value, report_errors, arg1, arg2, arg3, arg4 );
	}

	template<class T, class A1, class A2, class A3, class A4, class A5>
	T RunT( boost::python::object method, T default_value, A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5, bool report_errors = true  )
	{
		PYRUNMETHOD_RV(method, T, default_value, report_errors, arg1, arg2, arg3, arg4, arg5 );
	}

public:
	// Delayed delete list (to avoid crashes if we can't directly delete the object)
	void AddToDeleteList( boost::python::object inst );
	void CleanupDeleteList();
	
	// Tick and PerFrame registered methods
	void RegisterTickMethod( boost::python::object method, float ticksignal, bool looped=true, bool userealtime=false );
	void UnregisterTickMethod( boost::python::object method );
	boost::python::list GetRegisteredTickMethods();
	bool IsTickMethodRegistered( boost::python::object method );

	void UpdateRealtime();

	void RegisterPerFrameMethod( boost::python::object method );
	void UnregisterPerFrameMethod( boost::python::object method );
	boost::python::list GetRegisteredPerFrameMethods();
	bool IsPerFrameMethodRegistered( boost::python::object method );

#if defined(CLIENT_DLL) && defined(SRCPY_MOD_ENTITIES)
public:
	typedef struct py_delayed_data_update {
		EHANDLE hEnt;
		char name[_MAX_PATH];
		boost::python::object data;
		bool callchanged;
	} py_delayed_data_update;

	void AddToDelayedUpdateList( EHANDLE hEnt, char *name, boost::python::object data, bool callchanged=false );
	void PreProcessDelayedUpdates( CBaseEntity *pEntity );
	void PostProcessDelayedUpdates( CBaseEntity *pEntity );
#endif // CLIENT_DLL && SRCPY_MOD_ENTITIES

protected:
	void UpdateRealtimeTickMethods();
	void ExecuteAllScriptsInPath( const char *pPath );

private:
	bool m_bPythonRunning;
	bool m_bPythonIsFinalizing;
	bool m_bPathProtected;

	bool m_bActive;
	char m_LevelName[2048];

	// Delete list
	CUtlVector< boost::python::object > m_deleteList;

#if defined(CLIENT_DLL) && defined(SRCPY_MOD_ENTITIES)
	// Delete list
	CUtlVector< py_delayed_data_update > py_delayed_data_update_list;
#endif // CLIENT_DLL && SRCPY_MOD_ENTITIES

	// Tick and Frame registered methods
	typedef struct py_tick_methods {
		float m_fTickSignal;
		float m_fNextTickTime;
		bool m_bLooped;
		bool m_bUseRealTime;
		boost::python::object method;
	} py_tick_methods;
	CUtlVector< py_tick_methods > m_methodTickList;
	CUtlVector< boost::python::object > m_methodPerFrameList;
	boost::python::object m_activeMethod;
};

CSrcPython *SrcPySystem();

inline bool CSrcPython::IsPythonRunning( void ) 
{ 
	return m_bPythonRunning; 
}

inline bool CSrcPython::IsPythonFinalizing()
{
	return m_bPythonIsFinalizing;
}

inline bool CSrcPython::IsPathProtected()
{
	return m_bPathProtected;
}

inline int CSrcPython::GetInt(const char *name, const char *module, int default_value, bool report_error )
{
	return GetInt( name, Import(module), default_value, report_error );
}

inline float CSrcPython::GetFloat(const char *name, const char *module, float default_value, bool report_error )
{
	return GetFloat( name, Import(module), default_value, report_error );
}

inline const char *CSrcPython::GetString( const char *name, const char *module, const char *default_value, bool report_error )
{
	return GetString( name, Import(module), default_value, report_error );
}

inline Vector CSrcPython::GetVector( const char *name, const char *module, Vector default_value, bool report_error )
{
	return GetVector( name, Import(module), default_value, report_error );
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
inline void CSrcPython::AddToDeleteList( boost::python::object inst )
{
	m_deleteList.AddToTail( inst );
}

inline void CSrcPython::CleanupDeleteList( void )
{
	m_deleteList.RemoveAll();
}

#endif // SRCPY_H
