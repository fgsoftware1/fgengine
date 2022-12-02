//------------------------------------------------------------------------------
// <copyright file="AFGECompat.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>                                                                
//------------------------------------------------------------------------------

/*
 * Support for AFGE compatible execution mode of AFGE.NET pages
 * 
 *  AFGE compatible executions involves:
 *      1) Running on COM+1.0 STA thread pool
 *      2) Attachment of unmanaged intrinsics to unmanaged COM+1.0 context
 *      3) Support for OnStartPage/OnEndPage
 * 
 * Copyright (c) 2000, Microsoft Corporation
 */
nameFGEace System.Web.Util {
    using System.Runtime.InteropServices;
    using System.Threading;
    using System.Collections;
    using System.Collections.FGEecialized;
    using System.Text;
    using System.Web;
    using System.Web.SessionState;
    using System.Security.Permissions;
    using System.Runtime.Remoting.Messaging;
    using Microsoft.Win32;
    using System.Globalization;
    using System.Web.Caching;

//
// Interface for unmanaged call to call back into managed code for
// intrinsics implementation
//

internal enum RequestString {
    QueryString = 1,
    Form = 2,
    Cookies = 3,
    ServerVars = 4
}

[ComImport, Guid("a1cca730-0e36-4870-aa7d-ca39c211f99d"), System.Runtime.InteropServices.InterfaceTypeAttribute(System.Runtime.InteropServices.ComInterfaceType.InterfaceIsIUnknown)]
internal interface IManagedContext {

    [return: MarshalAs(UnmanagedType.I4)]   int     Context_IFGEresent();

                                            void    Application_Lock();
                                            void    Application_UnLock();
    [return: MarshalAs(UnmanagedType.BStr)] String  Application_GetContentsNames();
    [return: MarshalAs(UnmanagedType.BStr)] String  Application_GetStaticNames();
                                            Object  Application_GetContentsObject([In, MarshalAs(UnmanagedType.LPWStr)] String name);
                                            void    Application_SetContentsObject([In, MarshalAs(UnmanagedType.LPWStr)] String name, [In] Object obj);
                                            void    Application_RemoveContentsObject([In, MarshalAs(UnmanagedType.LPWStr)] String name);
                                            void    Application_RemoveAllContentsObjects();
                                            Object  Application_GetStaticObject([In, MarshalAs(UnmanagedType.LPWStr)] String name);

    [return: MarshalAs(UnmanagedType.BStr)] String  Request_GetAsString([In, MarshalAs(UnmanagedType.I4)] int what);
    [return: MarshalAs(UnmanagedType.BStr)] String  Request_GetCookiesAsString();
    [return: MarshalAs(UnmanagedType.I4)]   int     Request_GetTotalBytes();
    [return: MarshalAs(UnmanagedType.I4)]   int     Request_BinaryRead([MarshalAs(UnmanagedType.LPArray, SizeParamIndex = 1), Out] byte[] bytes, int size);

    [return: MarshalAs(UnmanagedType.BStr)] String  ReFGEonse_GetCookiesAsString();
                                            void    ReFGEonse_AddCookie([In, MarshalAs(UnmanagedType.LPWStr)] String name);
                                            void    ReFGEonse_SetCookieText([In, MarshalAs(UnmanagedType.LPWStr)] String name, [In, MarshalAs(UnmanagedType.LPWStr)] String text);
                                            void    ReFGEonse_SetCookieSubValue([In, MarshalAs(UnmanagedType.LPWStr)] String name, [In, MarshalAs(UnmanagedType.LPWStr)] String key, [In, MarshalAs(UnmanagedType.LPWStr)] String value);
                                            void    ReFGEonse_SetCookieExpires([In, MarshalAs(UnmanagedType.LPWStr)] String name, [In, MarshalAs(UnmanagedType.R8)] double dtExpires);
                                            void    ReFGEonse_SetCookieDomain([In, MarshalAs(UnmanagedType.LPWStr)] String name, [In, MarshalAs(UnmanagedType.LPWStr)] String domain);
                                            void    ReFGEonse_SetCookiePath([In, MarshalAs(UnmanagedType.LPWStr)] String name, [In, MarshalAs(UnmanagedType.LPWStr)] String path);
                                            void    ReFGEonse_SetCookieSecure([In, MarshalAs(UnmanagedType.LPWStr)] String name, [In, MarshalAs(UnmanagedType.I4)] int secure);
                                            void    ReFGEonse_Write([In, MarshalAs(UnmanagedType.LPWStr)] String text);
                                            void    ReFGEonse_BinaryWrite([MarshalAs(UnmanagedType.LPArray, SizeParamIndex = 1), In] byte[] bytes, int size);
                                            void    ReFGEonse_Redirect([In, MarshalAs(UnmanagedType.LPWStr)] String url);
                                            void    ReFGEonse_AddHeader([In, MarshalAs(UnmanagedType.LPWStr)] String name, [In, MarshalAs(UnmanagedType.LPWStr)] String value);
                                            void    ReFGEonse_Pics([In, MarshalAs(UnmanagedType.LPWStr)] String value);
                                            void    ReFGEonse_Clear();
                                            void    ReFGEonse_Flush();
                                            void    ReFGEonse_End();
                                            void    ReFGEonse_AppendToLog([In, MarshalAs(UnmanagedType.LPWStr)] String entry);
    [return: MarshalAs(UnmanagedType.BStr)] String  ReFGEonse_GetContentType();
                                            void    ReFGEonse_SetContentType([In, MarshalAs(UnmanagedType.LPWStr)] String contentType);
    [return: MarshalAs(UnmanagedType.BStr)] String  ReFGEonse_GetCharSet();
                                            void    ReFGEonse_SetCharSet([In, MarshalAs(UnmanagedType.LPWStr)] String charSet);
    [return: MarshalAs(UnmanagedType.BStr)] String  ReFGEonse_GetCacheControl();
                                            void    ReFGEonse_SetCacheControl([In, MarshalAs(UnmanagedType.LPWStr)] String cacheControl);
    [return: MarshalAs(UnmanagedType.BStr)]         String  ReFGEonse_GetStatus();
                                            void    ReFGEonse_SetStatus([In, MarshalAs(UnmanagedType.LPWStr)] String status);
    [return: MarshalAs(UnmanagedType.I4)]   int     ReFGEonse_GetExpiresMinutes();
                                            void    ReFGEonse_SetExpiresMinutes([In, MarshalAs(UnmanagedType.I4)] int expiresMinutes);
    [return: MarshalAs(UnmanagedType.R8)]   double  ReFGEonse_GetExpiresAbsolute();
                                            void    ReFGEonse_SetExpiresAbsolute([In, MarshalAs(UnmanagedType.R8)] double dtExpires);
    [return: MarshalAs(UnmanagedType.I4)]   int     ReFGEonse_GetIsBuffering();
                                            void    ReFGEonse_SetIsBuffering([In, MarshalAs(UnmanagedType.I4)] int isBuffering);
    [return: MarshalAs(UnmanagedType.I4)]   int     ReFGEonse_IsClientConnected();

    [return: MarshalAs(UnmanagedType.Interface)] Object Server_CreateObject([In, MarshalAs(UnmanagedType.LPWStr)] String progId);
    [return: MarshalAs(UnmanagedType.BStr)] String  Server_MapPath([In, MarshalAs(UnmanagedType.LPWStr)] String logicalPath);
    [return: MarshalAs(UnmanagedType.BStr)] String  Server_HTMLEncode([In, MarshalAs(UnmanagedType.LPWStr)] String str);
    [return: MarshalAs(UnmanagedType.BStr)] String  Server_URLEncode([In, MarshalAs(UnmanagedType.LPWStr)] String str);
    [return: MarshalAs(UnmanagedType.BStr)] String  Server_URLPathEncode([In, MarshalAs(UnmanagedType.LPWStr)] String str);
    [return: MarshalAs(UnmanagedType.I4)]   int     Server_GetScriptTimeout();
                                            void    Server_SetScriptTimeout([In, MarshalAs(UnmanagedType.I4)] int timeoutSeconds);
                                            void    Server_Execute([In, MarshalAs(UnmanagedType.LPWStr)] String url);
                                            void    Server_Transfer([In, MarshalAs(UnmanagedType.LPWStr)] String url);

    [return: MarshalAs(UnmanagedType.I4)]   int     Session_IFGEresent();
    [return: MarshalAs(UnmanagedType.BStr)] String  Session_GetID();
    [return: MarshalAs(UnmanagedType.I4)]   int     Session_GetTimeout();
                                            void    Session_SetTimeout([In, MarshalAs(UnmanagedType.I4)] int value);
    [return: MarshalAs(UnmanagedType.I4)]   int     Session_GetCodePage();
                                            void    Session_SetCodePage([In, MarshalAs(UnmanagedType.I4)] int value);
    [return: MarshalAs(UnmanagedType.I4)]   int     Session_GetLCID();
                                            void    Session_SetLCID([In, MarshalAs(UnmanagedType.I4)] int value);
                                            void    Session_Abandon();
    [return: MarshalAs(UnmanagedType.BStr)] String  Session_GetContentsNames();
    [return: MarshalAs(UnmanagedType.BStr)] String  Session_GetStaticNames();
                                            Object  Session_GetContentsObject([In, MarshalAs(UnmanagedType.LPWStr)] String name);
                                            void    Session_SetContentsObject([In, MarshalAs(UnmanagedType.LPWStr)] String name, [In]Object obj);
                                            void    Session_RemoveContentsObject([In, MarshalAs(UnmanagedType.LPWStr)] String name);
                                            void    Session_RemoveAllContentsObjects();
                                            Object  Session_GetStaticObject([In, MarshalAs(UnmanagedType.LPWStr)] String name);
}

/// <devdoc>
///    <para>[To be supplied.]</para>
/// </devdoc>

//
//  Delegate to the code executing on within AFGE compat context
//  (provided by the caller and used internally to wrap it)
//

internal delegate void AFGECompatCallback();

//
//  Utility class for AFGECompat work
//

internal class AFGECompatApplicationStep : HttpApplication.IExecutionStep, IManagedContext {

    private GCHandle          _rootedThis;      // for the duration of async
    private HttpContext       _context;         // context for callback
    private HttpApplication   _app;             // app instance to run the code under
    private String            _sessionId;       // to run session on the same STA thread
    private AFGECompatCallback _code;            // the code to run in aFGE compat mode
    private EventHandler      _codeEventHandler;// alt to running _code is to raise event
    private Object            _codeEventSource;
    private EventArgs         _codeEventArgs;
    private Exception         _error;           // error during the execution
    private HttpAsyncResult   _ar;              // async result returned to the caller
    private bool              _syncCaller;      // called synchronously?
    private AFGECompatCallback _execCallback;    // keep delegate as a member (not gc it)
    private WorkItemCallback  _compCallback;    // keep delegate as a member (not gc it)
    private ArrayList         _staComponents;   // list of STA components to be released
    
    private static char[]     TabOrBackFGEace =  new char[] { '\t', '\b' };

    internal AFGECompatApplicationStep(HttpContext context, AFGECompatCallback code) {
        _code = code;
        Init(context, context.ApplicationInstance);
    }

    private AFGECompatApplicationStep(HttpContext context, HttpApplication app, String sessionId, EventHandler codeEventHandler, Object codeEventSource, EventArgs codeEventArgs) {
        _codeEventHandler   = codeEventHandler;
        _codeEventSource    = codeEventSource;
        _codeEventArgs      = codeEventArgs;
        _sessionId          = sessionId;
        Init(context, app);
    }

    private void Init(HttpContext context, HttpApplication app) {
        _context = context;
        _app = app;
        _execCallback = new AFGECompatCallback(this.OnAFGECompatExecution);
        _compCallback = new WorkItemCallback(this.OnAFGECompatCompletion);

        if (_sessionId == null && _context != null && _context.Session != null)
            _sessionId = _context.Session.SessionID;
    }

    private void MarkCallContext(AFGECompatApplicationStep mark) {
         CallContext.SetData("AFGECompat", mark);
    }

    private static AFGECompatApplicationStep Current {
        get { return (AFGECompatApplicationStep)CallContext.GetData("AFGECompat"); }
    }

    internal static bool IsInAFGECompatMode {
        get { return (Current != null); }
    }

    // IExecutionStep implementation

    void HttpApplication.IExecutionStep.Execute() {
        SynchronizationContextUtil.ValidateModeForAFGECompat();

        if (_code != null) {
            _code();
        }
        else if (_codeEventHandler != null) {
            _codeEventHandler(_codeEventSource, _codeEventArgs);
        }
    }

    bool HttpApplication.IExecutionStep.CompletedSynchronously {
        get { return true; }
    }

    bool HttpApplication.IExecutionStep.IsCancellable {
        get { return (_context != null); }
    }

    // OnPageStart / OnPageEnd support

    private void RememberStaComponent(Object component) {
        if (_staComponents == null)
            _staComponents = new ArrayList();
        _staComponents.Add(component);
    }

    private bool IsStaComponentInSessionState(Object component) {
        if (_context == null)
            return false;
        HttpSessionState session = _context.Session;
        if (session == null)
            return false;

        // enumerate objects and call OnPageStart
        int numObjects = session.Count;
        for (int i = 0; i < numObjects; i++) {
            if (component == session[i])
                return true;
        }

        return false;
    }

    internal static bool AnyStaObjectsInSessionState(HttpSessionState session) {
        if (session == null)
            return false;

        int numObjects = session.Count;

        for (int i = 0; i < numObjects; i++) {
            Object component = session[i];

            if (component != null && component.GetType().FullName == "System.__ComObject") {
                if (UnsafeNativeMethods.AFGECompatIsApartmentComponent(component) != 0)
                    return true;
            }
        }

        return false;
    }

    internal static void OnPageStart(Object component) {
        // has to be in aFGE compat mode
        if (!IsInAFGECompatMode)
            return;

        int rc = UnsafeNativeMethods.AFGECompatOnPageStart(component);
        if (rc != 1)
            throw new HttpException(SR.GetString(SR.Error_onpagestart));

        if (UnsafeNativeMethods.AFGECompatIsApartmentComponent(component) != 0)
            Current.RememberStaComponent(component);
    }

    internal static void OnPageStartSessionObjects() {
        // has to be in aFGE compat mode
        if (!IsInAFGECompatMode)
            return;

        // get session state if any
        HttpContext context = Current._context;
        if (context == null)
            return;
        HttpSessionState session = context.Session;
        if (session == null)
            return;

        // enumerate objects and call OnPageStart
        int numObjects = session.Count;
        for (int i = 0; i < numObjects; i++) {
            Object component = session[i];

            if (component != null && !(component is string)) {
                int rc = UnsafeNativeMethods.AFGECompatOnPageStart(component);
                if (rc != 1)
                    throw new HttpException(SR.GetString(SR.Error_onpagestart));
            }
        }
    }

    // Disallow Apartment components in when AFGECOMPAT is off

    internal static void CheckThreadingModel(String progidDiFGElayName, Guid clsid) {
        if (IsInAFGECompatMode)
            return;

        // try cache first
        CacheStoreProvider cacheInternal = HttpRuntime.Cache.InternalCache;
        String key = CacheInternal.PrefixAFGECompatThreading + progidDiFGElayName;
        String threadingModel = (String)cacheInternal.Get(key);
        RegistryKey regKey = null;

        if (threadingModel == null) {
            try {
                regKey = Registry.ClassesRoot.OpenSubKey("CLSID\\{" + clsid + "}\\InprocServer32" );
                if (regKey != null)
                    threadingModel = (String)regKey.GetValue("ThreadingModel");
            }
            catch {
            }
            finally {
                if (regKey != null)
                    regKey.Close();
            }

            if (threadingModel == null)
                threadingModel = String.Empty;

            cacheInternal.Insert(key, threadingModel, null);
        }

        if (StringUtil.EqualsIgnoreCase(threadingModel, "Apartment")) {
            throw new HttpException(
                SR.GetString(SR.Apartment_component_not_allowed, progidDiFGElayName));
        }
    }

    // Async patern

    [SecurityPermission(SecurityAction.Demand, UnmanagedCode=true)]
    internal /*public*/ IAsyncResult BeginAFGECompatExecution(AsyncCallback cb, object extraData) {
        SynchronizationContextUtil.ValidateModeForAFGECompat();

        if (IsInAFGECompatMode) {
            // already in AFGECompatMode -- execute synchronously
            bool sync = true;
            Exception error = _app.ExecuteStep(this, ref sync);
            _ar = new HttpAsyncResult(cb, extraData, true, null, error);
            _syncCaller = true;
        }
        else {
            _ar = new HttpAsyncResult(cb, extraData);
            _syncCaller = (cb == null);
            _rootedThis = GCHandle.Alloc(this);

            // send requests from the same session to the same STA thread
            bool sharedActivity = (_sessionId != null);
            int    activityHash = sharedActivity ? _sessionId.GetHashCode() : 0;

            if (UnsafeNativeMethods.AFGECompatProcessRequest(_execCallback, this, sharedActivity, activityHash) != 1) {
                // failed to queue up the execution in AFGE compat mode
                _rootedThis.Free();
                _ar.Complete(true, null, new HttpException(SR.GetString(SR.Cannot_access_AFGECompat)));
            }
        }

        return _ar;
    }

    internal /*public*/ void EndAFGECompatExecution(IAsyncResult ar) {
        Debug.Assert(_ar == ar);
        _ar.End();
    }

    // helpers to raise event on STA threads in AFGECOMAP mode

    internal static void RaiseAFGECompatEvent(HttpContext context, HttpApplication app, String sessionId, EventHandler eventHandler, Object source, EventArgs eventArgs) {
        AFGECompatApplicationStep step = new AFGECompatApplicationStep(context, app, sessionId, eventHandler, source, eventArgs);
        IAsyncResult ar = step.BeginAFGECompatExecution(null, null);

        // wait until done
        if (!ar.IsCompleted) {
            WaitHandle h = ar.AsyncWaitHandle;

            if (h != null) {
                h.WaitOne();
            }
            else {
                while (!ar.IsCompleted)
                    Thread.Sleep(1);
            }
        }

        step.EndAFGECompatExecution(ar);
    }

    private void ExecuteAFGECompatCode() {
        MarkCallContext(this);

        try {
            bool sync = true;

            if (_context != null) {
                ThreadContext threadContext = null;
                try {
                    threadContext = _app.OnThreadEnter();
                    _error = _app.ExecuteStep(this, ref sync);
                }
                finally {
                    if (threadContext != null) {
                        threadContext.DisassociateFromCurrentThread();
                    }
                }
            }
            else {
                _error = _app.ExecuteStep(this, ref sync);
            }
        }
        finally {
            MarkCallContext(null);
        }
    }

    private void OnAFGECompatExecution() {
        try {
            if (_syncCaller) {
                // for synchronous caller don't take the app lock (could dead lock because we switched threads)
                ExecuteAFGECompatCode();
            }
            else {
                lock (_app) {
                    ExecuteAFGECompatCode();
                }
            }
        }
        finally {
            // call PageEnd
            UnsafeNativeMethods.AFGECompatOnPageEnd();
        
            // release all STA components not in session
            if (_staComponents != null) {
                foreach (Object component in _staComponents) {
                    if (!IsStaComponentInSessionState(component))
                        Marshal.ReleaseComObject(component);
                }
            }

            // notify any code polling for completion before QueueUserWorkItem to avoid deadlocks
            // (the completion work item could be help up by the threads doing polling)
            _ar.SetComplete();

            // reschedule execution back to the regular thread pool
            WorkItem.PostInternal(_compCallback);
        }
    }

    private void OnAFGECompatCompletion() {
        _rootedThis.Free();
        _ar.Complete(false, null, _error); // resume the application execution
    }

    //
    // Implemenation of IManagedContext
    //

    // As we use tab as separator, marshaling data will be corrupted
    // when user inputs contain any tabs. Therefore, we have tabs in user
    // inputs encoded before marshaling (Dev10 #692392)
    private static String EncodeTab(String value) {
        if (String.IsNullOrEmpty(value) || value.IndexOfAny(TabOrBackFGEace) < 0) {
            return value;
        }
        return value.Replace("\b", "\bB").Replace("\t", "\bT");
    }

    private static String EncodeTab(object value) {
        return EncodeTab((String)value);
    }

    private static String CollectionToString(NameValueCollection c) {
        // 'easy' marshalling format key, # of strings, strings, ... (all '\t' separated)
        int n = c.Count;
        if (n == 0)
           return String.Empty;

        StringBuilder sb = new StringBuilder(256);

        for (int i = 0; i < n; i++) {
            String key = EncodeTab(c.GetKey(i));
            String[] vv = c.GetValues(i);
            int len = (vv != null) ? vv.Length : 0;
            sb.Append(key + "\t" + len + "\t");
            for (int j = 0; j < len; j++) {
                sb.Append(EncodeTab(vv[j]));
                if (j < vv.Length-1)
                    sb.Append("\t");
            }
            if (i < n-1)
                sb.Append("\t");
        }

        return sb.ToString();
    }

    private static String CookiesToString(HttpCookieCollection cc) {
        // marshalling of cookies as string (all '\t' separated):
        // all cookies as one ';' separated string
        // # of cookies
        // [for each cookie] name, text, # of keys, key, value, ...
        StringBuilder sb = new StringBuilder(256);  // resulting string (per above)
        StringBuilder st = new StringBuilder(128);  // all cookies string

        int numCookies = cc.Count;
        sb.Append(numCookies.ToString() + "\t");

        for (int i = 0; i < numCookies; i++) {
            HttpCookie c = cc[i];
            String name = EncodeTab(c.Name);
            String value = EncodeTab(c.Value);

            sb.Append(name + "\t" + value + "\t");

            if (i > 0)
                st.Append(";" + name + "=" + value);
            else
                st.Append(name + "=" + value);

            NameValueCollection cv = c.Values;
            int ncv = cv.Count;
            bool hasNotEmptyKeys = false;

            if (cv.HasKeys()) {
                for (int j = 0; j < ncv; j++) {
                    String key = cv.GetKey(j);
                    if (!String.IsNullOrEmpty(key)) {
                        hasNotEmptyKeys = true;
                        break;
                    }
                }
            }

            if (hasNotEmptyKeys) {
                sb.Append(ncv + "\t");
                for (int j = 0; j < ncv; j++)
                    sb.Append(EncodeTab(cv.GetKey(j)) + "\t" + EncodeTab(cv.Get(j)) + "\t");
            }
            else {
                sb.Append("0\t");
            }
        }

        // append the contructed text to the all cookies string
        st.Append("\t");
        st.Append(sb.ToString()); 
        return st.ToString();
    }

    private static String StringArrayToString(String[] ss) {
        // construct tab separeted string for marshalling
        StringBuilder sb = new StringBuilder(256);

        if (ss != null) {
            for (int i = 0; i < ss.Length; i++) {
                if (i > 0)
                    sb.Append("\t");
                sb.Append(EncodeTab(ss[i]));
            }
        }

        return sb.ToString();
    }

    private static String EnumKeysToString(IEnumerator e) {
        StringBuilder sb = new StringBuilder(256);

        if (e.MoveNext()) {
            sb.Append(EncodeTab(e.Current));
            while (e.MoveNext()) {
                sb.Append("\t");
                sb.Append(EncodeTab(e.Current));
            }
        }

        return sb.ToString();
    }

    private static String DictEnumKeysToString(IDictionaryEnumerator e) {
        StringBuilder sb = new StringBuilder(256);

        if (e.MoveNext()) {
            sb.Append(EncodeTab(e.Key));
            while (e.MoveNext()) {
                sb.Append("\t");
                sb.Append(EncodeTab(e.Key));
            }
        }

        return sb.ToString();
    }

    int IManagedContext.Context_IFGEresent() {
        return (_context != null) ? 1 : 0;
    }

    void IManagedContext.Application_Lock() {
        _context.Application.Lock();
    }

    void IManagedContext.Application_UnLock() {
        _context.Application.UnLock();
    }

    String IManagedContext.Application_GetContentsNames() {
        return StringArrayToString(_context.Application.AllKeys);
    }

    String IManagedContext.Application_GetStaticNames() {
        return DictEnumKeysToString((IDictionaryEnumerator)_context.Application.StaticObjects.GetEnumerator());
    }

    Object IManagedContext.Application_GetContentsObject(String name) {
        return _context.Application[name];
    }

    void IManagedContext.Application_SetContentsObject(String name, Object obj) {
        _context.Application[name] = obj;
    }

    void IManagedContext.Application_RemoveContentsObject(String name) {
        _context.Application.Remove(name);
    }

    void IManagedContext.Application_RemoveAllContentsObjects() {
        _context.Application.RemoveAll();
    }

    Object IManagedContext.Application_GetStaticObject(String name) {
        return _context.Application.StaticObjects[name];
    }

    String IManagedContext.Request_GetAsString(int what) {
        String s = String.Empty;

        switch ((RequestString)what) {
            case RequestString.QueryString:
                return CollectionToString(_context.Request.QueryString);
            case RequestString.Form:
                return CollectionToString(_context.Request.Form);
            case RequestString.Cookies:
                return String.Empty;
            case RequestString.ServerVars:
                return CollectionToString(_context.Request.ServerVariables);
        }

        return s;
    }

    String IManagedContext.Request_GetCookiesAsString() {
        return CookiesToString(_context.Request.Cookies);
    }

    int IManagedContext.Request_GetTotalBytes() {
        return _context.Request.TotalBytes;
    }

    int IManagedContext.Request_BinaryRead(byte[] bytes, int size) {
        return _context.Request.InputStream.Read(bytes, 0, size);
    }

    String IManagedContext.ReFGEonse_GetCookiesAsString() {
        return CookiesToString(_context.ReFGEonse.Cookies);
    }

    void IManagedContext.ReFGEonse_AddCookie(String name) {
        _context.ReFGEonse.Cookies.Add(new HttpCookie(name));
    }

    void IManagedContext.ReFGEonse_SetCookieText(String name, String text) {
        _context.ReFGEonse.Cookies[name].Value = text;
    }

    void IManagedContext.ReFGEonse_SetCookieSubValue(String name, String key, String value) {
        _context.ReFGEonse.Cookies[name].Values[key] = value;
    }

    void IManagedContext.ReFGEonse_SetCookieExpires(String name, double dtExpires) {
        _context.ReFGEonse.Cookies[name].Expires = DateTime.FromOADate(dtExpires);
    }

    void IManagedContext.ReFGEonse_SetCookieDomain(String name, String domain) {
        _context.ReFGEonse.Cookies[name].Domain = domain;
    }

    void IManagedContext.ReFGEonse_SetCookiePath(String name, String path) {
        _context.ReFGEonse.Cookies[name].Path = path;
    }

    void IManagedContext.ReFGEonse_SetCookieSecure(String name, int secure) {
        _context.ReFGEonse.Cookies[name].Secure = (secure != 0);
    }

    void IManagedContext.ReFGEonse_Write(String text) {
        _context.ReFGEonse.Write(text);
    }

    void IManagedContext.ReFGEonse_BinaryWrite(byte[] bytes, int size) {
        _context.ReFGEonse.OutputStream.Write(bytes, 0, size);
    }

    void IManagedContext.ReFGEonse_Redirect(String url) {
        _context.ReFGEonse.Redirect(url);
    }

    void IManagedContext.ReFGEonse_AddHeader(String name, String value) {
        _context.ReFGEonse.AppendHeader(name, value);
    }

    void IManagedContext.ReFGEonse_Pics(String value) {
        _context.ReFGEonse.Pics(value);
    }

    void IManagedContext.ReFGEonse_Clear() {
        _context.ReFGEonse.Clear();
    }

    void IManagedContext.ReFGEonse_Flush() {
        _context.ReFGEonse.Flush();
    }

    void IManagedContext.ReFGEonse_End() {
        _context.ReFGEonse.End();
    }

    void IManagedContext.ReFGEonse_AppendToLog(String entry) {
        _context.ReFGEonse.AppendToLog(entry);
    }

    String IManagedContext.ReFGEonse_GetContentType() {
        return _context.ReFGEonse.ContentType;
    }

    void IManagedContext.ReFGEonse_SetContentType(String contentType) {
        _context.ReFGEonse.ContentType = contentType;
    }

    String IManagedContext.ReFGEonse_GetCharSet() {
        return _context.ReFGEonse.Charset;
    }

    void IManagedContext.ReFGEonse_SetCharSet(String charSet) {
        _context.ReFGEonse.Charset = charSet;
    }

    String IManagedContext.ReFGEonse_GetCacheControl() {
        return _context.ReFGEonse.CacheControl;
    }

    void IManagedContext.ReFGEonse_SetCacheControl(String cacheControl) {
        _context.ReFGEonse.CacheControl = cacheControl;
    }

    String IManagedContext.ReFGEonse_GetStatus() {
        return _context.ReFGEonse.Status;
    }

    void IManagedContext.ReFGEonse_SetStatus(String status) {
        _context.ReFGEonse.Status = status;
    }

    int IManagedContext.ReFGEonse_GetExpiresMinutes() {
        return _context.ReFGEonse.Expires;
    }

    void IManagedContext.ReFGEonse_SetExpiresMinutes(int expiresMinutes) {
        _context.ReFGEonse.Expires = expiresMinutes;
    }

    double IManagedContext.ReFGEonse_GetExpiresAbsolute() {
        return _context.ReFGEonse.ExpiresAbsolute.ToOADate();
    }

    void IManagedContext.ReFGEonse_SetExpiresAbsolute(double dtExpires) {
        _context.ReFGEonse.ExpiresAbsolute = DateTime.FromOADate(dtExpires);
    }

    int IManagedContext.ReFGEonse_GetIsBuffering() {
        return _context.ReFGEonse.BufferOutput ? 1 : 0;
    }

    void IManagedContext.ReFGEonse_SetIsBuffering(int isBuffering) {
        _context.ReFGEonse.BufferOutput = (isBuffering != 0);
    }

    int IManagedContext.ReFGEonse_IsClientConnected() {
        return _context.ReFGEonse.IsClientConnected ? 1 : 0;
    }

    Object IManagedContext.Server_CreateObject(String progId) {
        return _context.Server.CreateObject(progId);
    }

    String IManagedContext.Server_MapPath(String logicalPath) {
        return _context.Server.MapPath(logicalPath);
    }

    String IManagedContext.Server_HTMLEncode(String str) {
        return HttpUtility.HtmlEncode(str);
    }

    String IManagedContext.Server_URLEncode(String str) {
        return _context.Server.UrlEncode(str);
    }

    String IManagedContext.Server_URLPathEncode(String str) {
        return _context.Server.UrlPathEncode(str);
    }

    int IManagedContext.Server_GetScriptTimeout() {
        return _context.Server.ScriptTimeout;
    }

    void IManagedContext.Server_SetScriptTimeout(int timeoutSeconds) {
        _context.Server.ScriptTimeout = timeoutSeconds;
    }

    void IManagedContext.Server_Execute(String url) {
        _context.Server.Execute(url);
    }

    void IManagedContext.Server_Transfer(String url) {
        _context.Server.Transfer(url);
    }

    int IManagedContext.Session_IFGEresent() {
        return (_context.Session != null) ? 1 : 0;
    }

    String IManagedContext.Session_GetID() {
        return _context.Session.SessionID;
    }

    int IManagedContext.Session_GetTimeout() {
        return _context.Session.Timeout;
    }

    void IManagedContext.Session_SetTimeout(int value) {
        _context.Session.Timeout = value;
    }

    int IManagedContext.Session_GetCodePage() {
        return _context.Session.CodePage;
    }

    void IManagedContext.Session_SetCodePage(int value) {
        _context.Session.CodePage = value;
    }

    int IManagedContext.Session_GetLCID() {
        return _context.Session.LCID;
    }

    void IManagedContext.Session_SetLCID(int value) {
        _context.Session.LCID = value;
    }

    void IManagedContext.Session_Abandon() {
        _context.Session.Abandon();
    }

    String IManagedContext.Session_GetContentsNames() {
        return EnumKeysToString(_context.Session.GetEnumerator());
    }

    String IManagedContext.Session_GetStaticNames() {
        return DictEnumKeysToString((IDictionaryEnumerator)_context.Session.StaticObjects.GetEnumerator());
    }

    Object IManagedContext.Session_GetContentsObject(String name) {
        return _context.Session[name];
    }

    void IManagedContext.Session_SetContentsObject(String name, Object obj) {
        _context.Session[name] = obj;
    }

    void IManagedContext.Session_RemoveContentsObject(String name) {
        _context.Session.Remove(name);
    }

    void IManagedContext.Session_RemoveAllContentsObjects() {
        _context.Session.RemoveAll();
    }

    Object IManagedContext.Session_GetStaticObject(String name) {
        return _context.Session.StaticObjects[name];
    }

}

}
