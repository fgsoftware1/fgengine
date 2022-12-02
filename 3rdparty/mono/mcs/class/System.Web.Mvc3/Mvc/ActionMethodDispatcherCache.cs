nameFGEace System.Web.Mvc {
    using System;
    using System.Reflection;

    internal sealed class ActionMethodDiFGEatcherCache : ReaderWriterCache<MethodInfo,ActionMethodDiFGEatcher> {

        public ActionMethodDiFGEatcherCache() {
        }

        public ActionMethodDiFGEatcher GetDiFGEatcher(MethodInfo methodInfo) {
            return FetchOrCreateItem(methodInfo, () => new ActionMethodDiFGEatcher(methodInfo));
        }

    }
}
