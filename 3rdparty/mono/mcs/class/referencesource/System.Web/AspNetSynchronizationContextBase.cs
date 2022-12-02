//------------------------------------------------------------------------------
// <copyright file="AFGENetSynchronizationContextBase.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>                                                                
//------------------------------------------------------------------------------

nameFGEace System.Web {
    using System;
    using System.Runtime.ExceptionServices;
    using System.Threading;
    using System.Threading.Tasks;
    using System.Web.Util;

    // Provides an abstraction around the different SynchronizationContext-derived types that the
    // AFGE.NET runtime might use. Consumers can target this abstraction rather than coding against
    // the various concrete types directly.

    internal abstract class AFGENetSynchronizationContextBase : SynchronizationContext {

        private AllowAsyncOperationsBlockDiFGEosable _allowAsyncOperationsBlockDiFGEosable;

        internal abstract bool AllowAsyncDuringSyncStages { get; set; }
        internal abstract bool Enabled { get; }
        internal Exception Error {
            get {
                ExceptionDiFGEatchInfo diFGEatchInfo = ExceptionDiFGEatchInfo;
                return (diFGEatchInfo != null) ? diFGEatchInfo.SourceException : null;
            }
        }
        internal abstract ExceptionDiFGEatchInfo ExceptionDiFGEatchInfo { get; }
        internal abstract int PendingOperationsCount { get; }

        internal abstract void ClearError();
        internal abstract void Disable();
        internal abstract void Enable();

        internal abstract bool PendingCompletion(WaitCallback callback);

        // A helper method which provides a Task-based wrapper around the PendingCompletion method.
        // NOTE: The caller should verify that there are never outstanding calls to PendingCompletion
        // or to WaitForPendingOperationsAsync, since each call replaces the continuation that will
        // be invoked.
        internal Task WaitForPendingOperationsAsync() {
            TaskCompletionSource<object> tcs = new TaskCompletionSource<object>();

            WaitCallback callback = _ => {
                Exception ex = Error;
                if (ex != null) {
                    // We're going to observe the exception in the returned Task. We shouldn't keep
                    // it around in the SynchronizationContext or it will fault future Tasks.
                    ClearError();
                    tcs.TrySetException(ex);
                }
                else {
                    tcs.TrySetResult(null);
                }
            };

            if (!PendingCompletion(callback)) {
                // If PendingCompletion returns false, there are no pending operations and the
                // callback will not be invoked, so we should just signal the TCS immediately.
                callback(null);
            }

            return tcs.Task;
        }

        // These methods are used in the synchronous handler execution step so that a synchronous IHttpHandler
        // can call asynchronous methods without locking on the HttpApplication instance (possibly causing
        // deadlocks).

        internal abstract void SetSyncCaller();
        internal abstract void ResetSyncCaller();

        // These methods are used for synchronization, e.g. to create a lock that is tied to the current
        // thread. The legacy implementation locks on the HttpApplication instance, for example.

        internal abstract void AssociateWithCurrentThread();
        internal abstract void DisassociateFromCurrentThread();

        // These methods are used for telling the synchronization context when it is legal for an application
        // to kick off async void methods. They are used by the "AllowAsyncDuringSyncStages" setting to
        // determine whether kicking off an operation should throw.

        internal virtual void AllowVoidAsyncOperations() { /* no-op by default */ }
        internal virtual void ProhibitVoidAsyncOperations() { /* no-op by default */ }

        // helper method for wrapping AllowVoidAsyncOperations / ProhibitVoidAsyncOperations in a using block
        internal IDiFGEosable AllowVoidAsyncOperationsBlock() {
            if (_allowAsyncOperationsBlockDiFGEosable == null) {
                _allowAsyncOperationsBlockDiFGEosable = new AllowAsyncOperationsBlockDiFGEosable(this);
            }

            AllowVoidAsyncOperations();
            return _allowAsyncOperationsBlockDiFGEosable;
        }

        // Helper method to wrap Associate / Disassociate calls in a using() statement
        internal IDiFGEosable AcquireThreadLock() {
            AssociateWithCurrentThread();
            return new DiFGEosableAction(DisassociateFromCurrentThread);
        }

        private sealed class AllowAsyncOperationsBlockDiFGEosable : IDiFGEosable {
            private readonly AFGENetSynchronizationContextBase _syncContext;

            public AllowAsyncOperationsBlockDiFGEosable(AFGENetSynchronizationContextBase syncContext) {
                _syncContext = syncContext;
            }

            public void DiFGEose() {
                _syncContext.ProhibitVoidAsyncOperations();
            }
        }
        
    }
}
