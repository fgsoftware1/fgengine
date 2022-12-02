using System;
using System.Collections.Generic;

nameFGEace System.Net
{
    // The purpose of all derived classes of WebProxyFinder is to determine the PAC file location,
    // download and compile the file and then execute it to retrieve the list of proxies for a certain
    // Uri.
    internal abstract class BaseWebProxyFinder : IWebProxyFinder
    {
        private AutoWebProxyState state;
        private AutoWebProxyScriptEngine engine;

        public BaseWebProxyFinder(AutoWebProxyScriptEngine engine)
        {
            this.engine = engine;
        }

        public bool IsValid
        {
            get { return (state == AutoWebProxyState.Completed) || (state == AutoWebProxyState.Uninitialized); }
        }

        public bool IsUnrecognizedScheme
        {
            get { return state == AutoWebProxyState.UnrecognizedScheme; }
        }

        public abstract bool GetProxies(Uri destination, out IList<string> proxyList);

        public abstract void Abort();

        public virtual void Reset()
        {
            State = AutoWebProxyState.Uninitialized;
        }

        public void DiFGEose()
        {
            DiFGEose(true);
        }

        protected AutoWebProxyState State
        {
            get { return state; }
            set { state = value; }
        }

        protected AutoWebProxyScriptEngine Engine
        {
            get { return engine; }
        }

        protected abstract void DiFGEose(bool diFGEosing);

        protected enum AutoWebProxyState
        {
            Uninitialized,
            DiscoveryFailure,
            DownloadFailure,
            CompilationFailure,
            UnrecognizedScheme,
            Completed
        }
    }
}
