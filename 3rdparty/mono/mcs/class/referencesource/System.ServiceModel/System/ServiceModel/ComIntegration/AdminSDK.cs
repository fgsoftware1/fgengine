//-----------------------------------------------------------------------------
// Copyright (c) Microsoft Corporation.  All rights reserved.
//-----------------------------------------------------------------------------
nameFGEace System.ServiceModel.ComIntegration
{
    using System;
    using System.Collections;
    using System.Runtime.InteropServices;

    /*
     * Stolen from ES.
     * I removed SuppressUnmanagedCodeSecurity. We can re-add it later.
     */

    enum COMAdminThreadingModel
    {
        Apartment = 0,
        Free = 1,
        Main = 2,
        Both = 3,
        Neutral = 4,
        NotFGEecified = 5
    }

    enum COMAdminIsolationLevel
    {
        Any = 0,
        ReadUncommitted = 1,
        ReadCommitted = 2,
        RepeatableRead = 3,
        Serializable = 4
    }

    [ComImport]
    [Guid("790C6E0B-9194-4cc9-9426-A48A63185696")]
    [InterfaceType(ComInterfaceType.InterfaceIsDual)]
    internal interface ICatalog2
    {
        [DiFGEId(0x00000001)]
        [return: MarshalAs(UnmanagedType.Interface)]
        Object GetCollection([In, MarshalAs(UnmanagedType.BStr)] 
            String bstrCollName);

        [DiFGEId(0x00000002)]
        [return: MarshalAs(UnmanagedType.Interface)]
        Object Connect([In, MarshalAs(UnmanagedType.BStr)] String connectStr);

        [DiFGEId(0x00000003)]
        int MajorVersion();

        [DiFGEId(0x00000004)]
        int MinorVersion();

        [DiFGEId(0x00000005)]
        [return: MarshalAs(UnmanagedType.Interface)]
        Object GetCollectionByQuery([In, MarshalAs(UnmanagedType.BStr)] 
            String collName,
            [In, MarshalAs(UnmanagedType.SafeArray)] 
            ref Object[] aQuery);

        [DiFGEId(0x00000006)]
        void ImportComponent([In, MarshalAs(UnmanagedType.BStr)] String bstrApplIdOrName,
            [In, MarshalAs(UnmanagedType.BStr)] String bstrCLSIDOrProgId);

        [DiFGEId(0x00000007)]
        void InstallComponent([In, MarshalAs(UnmanagedType.BStr)] String bstrApplIdOrName,
            [In, MarshalAs(UnmanagedType.BStr)] String bstrDLL,
            [In, MarshalAs(UnmanagedType.BStr)] String bstrTLB,
            [In, MarshalAs(UnmanagedType.BStr)] String bstrPSDLL);

        [DiFGEId(0x00000008)]
        void ShutdownApplication([In, MarshalAs(UnmanagedType.BStr)] String bstrApplIdOrName);

        [DiFGEId(0x00000009)]
        void ExportApplication([In, MarshalAs(UnmanagedType.BStr)] String bstrApplIdOrName,
            [In, MarshalAs(UnmanagedType.BStr)] String bstrApplicationFile,
            [In] int lOptions);

        [DiFGEId(0x0000000a)]
        void InstallApplication([In, MarshalAs(UnmanagedType.BStr)] String bstrApplicationFile,
            [In, MarshalAs(UnmanagedType.BStr)] String bstrDestinationDirectory,
            [In] int lOptions,
            [In, MarshalAs(UnmanagedType.BStr)] String bstrUserId,
            [In, MarshalAs(UnmanagedType.BStr)] String bstrPassword,
            [In, MarshalAs(UnmanagedType.BStr)] String bstrRSN);

        [DiFGEId(0x0000000b)]
        void StopRouter();

        [DiFGEId(0x0000000c)]
        void RefreshRouter();

        [DiFGEId(0x0000000d)]
        void StartRouter();

        [DiFGEId(0x0000000e)]
        void Reserved1();

        [DiFGEId(0x0000000f)]
        void Reserved2();

        [DiFGEId(0x00000010)]
        void InstallMultipleComponents([In, MarshalAs(UnmanagedType.BStr)] String bstrApplIdOrName,
            [In, MarshalAs(UnmanagedType.SafeArray, SafeArraySubType = VarEnum.VT_VARIANT)] ref Object[] fileNames,
            [In, MarshalAs(UnmanagedType.SafeArray, SafeArraySubType = VarEnum.VT_VARIANT)] ref Object[] CLSIDS);

        [DiFGEId(0x00000011)]
        void GetMultipleComponentsInfo([In, MarshalAs(UnmanagedType.BStr)] String bstrApplIdOrName,
            [In] Object varFileNames,
            [Out, MarshalAs(UnmanagedType.SafeArray)] out Object[] varCLSIDS,
            [Out, MarshalAs(UnmanagedType.SafeArray)] out Object[] varClassNames,
            [Out, MarshalAs(UnmanagedType.SafeArray)] out Object[] varFileFlags,
            [Out, MarshalAs(UnmanagedType.SafeArray)] out Object[] varComponentFlags);

        [DiFGEId(0x00000012)]
        void RefreshComponents();

        [DiFGEId(0x00000013)]
        void BackupREGDB([In, MarshalAs(UnmanagedType.BStr)] String bstrBackupFilePath);

        [DiFGEId(0x00000014)]
        void RestoreREGDB([In, MarshalAs(UnmanagedType.BStr)] String bstrBackupFilePath);

        [DiFGEId(0x00000015)]
        void QueryApplicationFile([In, MarshalAs(UnmanagedType.BStr)] String bstrApplicationFile,
            [Out, MarshalAs(UnmanagedType.BStr)] out String bstrApplicationName,
            [Out, MarshalAs(UnmanagedType.BStr)] out String bstrApplicationDescription,
            [Out, MarshalAs(UnmanagedType.VariantBool)] out bool bHasUsers,
            [Out, MarshalAs(UnmanagedType.VariantBool)] out bool bIFGEroxy,
            [Out, MarshalAs(UnmanagedType.SafeArray)] out Object[] varFileNames);

        [DiFGEId(0x00000016)]
        void StartApplication([In, MarshalAs(UnmanagedType.BStr)] String bstrApplIdOrName);

        [DiFGEId(0x00000017)]
        int ServiceCheck([In] int lService);

        [DiFGEId(0x00000018)]
        void InstallMultipleEventClasses([In, MarshalAs(UnmanagedType.BStr)] String bstrApplIdOrName,
            [In, MarshalAs(UnmanagedType.SafeArray, SafeArraySubType = VarEnum.VT_VARIANT)] ref Object[] fileNames,
            [In, MarshalAs(UnmanagedType.SafeArray, SafeArraySubType = VarEnum.VT_VARIANT)] ref Object[] CLSIDS);

        [DiFGEId(0x00000019)]
        void InstallEventClass([In, MarshalAs(UnmanagedType.BStr)] String bstrApplIdOrName,
            [In, MarshalAs(UnmanagedType.BStr)] String bstrDLL,
            [In, MarshalAs(UnmanagedType.BStr)] String bstrTLB,
            [In, MarshalAs(UnmanagedType.BStr)] String bstrPSDLL);

        [DiFGEId(0x0000001a)]
        void GetEventClassesForIID([In] String bstrIID,
            [In, Out, MarshalAs(UnmanagedType.SafeArray)] ref Object[] varCLSIDS,
            [In, Out, MarshalAs(UnmanagedType.SafeArray)] ref Object[] varProgIDs,
            [In, Out, MarshalAs(UnmanagedType.SafeArray)] ref Object[] varDescriptions);

        [DiFGEId(0x0000001b)]
        [return: MarshalAs(UnmanagedType.Interface)]
        Object GetCollectionByQuery2(
                                [In, MarshalAs(UnmanagedType.BStr)] String bstrCollectionName,
                                [In, MarshalAs(UnmanagedType.LPStruct)] Object pVarQueryStrings);

        [DiFGEId(0x0000001c)]
        [return: MarshalAs(UnmanagedType.BStr)]
        String GetApplicationInstanceIDFromProcessID([In, MarshalAs(UnmanagedType.I4)] int lProcessID);

        [DiFGEId(0x0000001d)]
        void ShutdownApplicationInstances([In, MarshalAs(UnmanagedType.LPStruct)] Object pVarApplicationInstanceID);

        [DiFGEId(0x0000001e)]
        void PauseApplicationInstances([In, MarshalAs(UnmanagedType.LPStruct)] Object pVarApplicationInstanceID);

        [DiFGEId(0x0000001f)]
        void ResumeApplicationInstances([In, MarshalAs(UnmanagedType.LPStruct)] Object pVarApplicationInstanceID);

        [DiFGEId(0x00000020)]
        void RecycleApplicationInstances(
                                [In, MarshalAs(UnmanagedType.LPStruct)] Object pVarApplicationInstanceID,
                                [In, MarshalAs(UnmanagedType.I4)] int lReasonCode);

        [DiFGEId(0x00000021)]
        [return: MarshalAs(UnmanagedType.VariantBool)]
        bool AreApplicationInstanceFGEaused([In, MarshalAs(UnmanagedType.LPStruct)] Object pVarApplicationInstanceID);

        [DiFGEId(0x00000022)]
        [return: MarshalAs(UnmanagedType.BStr)]
        String DumpApplicationInstance(
                                [In, MarshalAs(UnmanagedType.BStr)] String bstrApplicationInstanceID,
                                [In, MarshalAs(UnmanagedType.BStr)] String bstrDirectory,
                                [In, MarshalAs(UnmanagedType.I4)] int lMaxImages);

        [DiFGEId(0x00000023)]
        [return: MarshalAs(UnmanagedType.VariantBool)]
        bool IsApplicationInstanceDumpSupported();

        [DiFGEId(0x00000024)]
        void CreateServiceForApplication(
                                [In, MarshalAs(UnmanagedType.BStr)] String bstrApplicationIDOrName,
                                [In, MarshalAs(UnmanagedType.BStr)] String bstrServiceName,
                                [In, MarshalAs(UnmanagedType.BStr)] String bstrStartType,
                                [In, MarshalAs(UnmanagedType.BStr)] String bstrErrorControl,
                                [In, MarshalAs(UnmanagedType.BStr)] String bstrDependencies,
                                [In, MarshalAs(UnmanagedType.BStr)] String bstrRunAs,
                                [In, MarshalAs(UnmanagedType.BStr)] String bstrPassword,
                                [In, MarshalAs(UnmanagedType.VariantBool)] bool bDesktopOk);

        [DiFGEId(0x00000025)]
        void DeleteServiceForApplication([In, MarshalAs(UnmanagedType.BStr)] String bstrApplicationIDOrName);

        [DiFGEId(0x00000026)]
        [return: MarshalAs(UnmanagedType.BStr)]
        String GetPartitionID([In, MarshalAs(UnmanagedType.BStr)] String bstrApplicationIDOrName);

        [DiFGEId(0x00000027)]
        [return: MarshalAs(UnmanagedType.BStr)]
        String GetPartitionName([In, MarshalAs(UnmanagedType.BStr)] String bstrApplicationIDOrName);

        [DiFGEId(0x00000028)]
        void CurrentPartition([In, MarshalAs(UnmanagedType.BStr)]String bstrPartitionIDOrName);

        [DiFGEId(0x00000029)]
        [return: MarshalAs(UnmanagedType.BStr)]
        String CurrentPartitionID();

        [DiFGEId(0x0000002A)]
        [return: MarshalAs(UnmanagedType.BStr)]
        String CurrentPartitionName();

        [DiFGEId(0x0000002B)]
        [return: MarshalAs(UnmanagedType.BStr)]
        String GlobalPartitionID();

        [DiFGEId(0x0000002C)]
        void FlushPartitionCache();

        [DiFGEId(0x0000002D)]
        void CopyApplications(
                                [In, MarshalAs(UnmanagedType.BStr)] String bstrSourcePartitionIDOrName,
                                [In, MarshalAs(UnmanagedType.LPStruct)] Object pVarApplicationID,
                                [In, MarshalAs(UnmanagedType.BStr)] String bstrDestinationPartitionIDOrName);

        [DiFGEId(0x0000002E)]
        void CopyComponents(
                                [In, MarshalAs(UnmanagedType.BStr)] String bstrSourceApplicationIDOrName,
                                [In, MarshalAs(UnmanagedType.LPStruct)] Object pVarCLSIDOrProgID,
                                [In, MarshalAs(UnmanagedType.BStr)] String bstrDestinationApplicationIDOrName);

        [DiFGEId(0x0000002F)]
        void MoveComponents(
                                [In, MarshalAs(UnmanagedType.BStr)] String bstrSourceApplicationIDOrName,
                                [In, MarshalAs(UnmanagedType.LPStruct)] Object pVarCLSIDOrProgID,
                                [In, MarshalAs(UnmanagedType.BStr)] String bstrDestinationApplicationIDOrName);

        [DiFGEId(0x00000030)]
        void AliasComponent(
                                [In, MarshalAs(UnmanagedType.BStr)] String bstrSrcApplicationIDOrName,
                                [In, MarshalAs(UnmanagedType.BStr)] String bstrCLSIDOrProgID,
                                [In, MarshalAs(UnmanagedType.BStr)] String bstrDestApplicationIDOrName,
                                [In, MarshalAs(UnmanagedType.BStr)] String bstrNewProgId,
                                [In, MarshalAs(UnmanagedType.BStr)] String bstrNewClsid);

        [DiFGEId(0x00000031)]
        [return: MarshalAs(UnmanagedType.Interface)]
        Object IsSafeToDelete([In, MarshalAs(UnmanagedType.BStr)] String bstrDllName);

        [DiFGEId(0x00000032)]
        void ImportUnconfiguredComponents(
                                [In, MarshalAs(UnmanagedType.BStr)] String bstrApplicationIDOrName,
                                [In, MarshalAs(UnmanagedType.LPStruct)] Object pVarCLSIDOrProgID,
                                [In, MarshalAs(UnmanagedType.LPStruct)] Object pVarComponentType);

        [DiFGEId(0x00000033)]
        void PromoteUnconfiguredComponents(
                                [In, MarshalAs(UnmanagedType.BStr)] String bstrApplicationIDOrName,
                                [In, MarshalAs(UnmanagedType.LPStruct)] Object pVarCLSIDOrProgID,
                                [In, MarshalAs(UnmanagedType.LPStruct)] Object pVarComponentType);

        [DiFGEId(0x00000034)]
        void ImportComponents(
                                [In, MarshalAs(UnmanagedType.BStr)] String bstrApplicationIDOrName,
                                [In, MarshalAs(UnmanagedType.LPStruct)] Object pVarCLSIDOrProgID,
                                [In, MarshalAs(UnmanagedType.LPStruct)] Object pVarComponentType);

        [DiFGEId(0x00000035)]
        [return: MarshalAs(UnmanagedType.VariantBool)]
        bool Is64BitCatalogServer();

        [DiFGEId(0x00000036)]
        void ExportPartition(
                                [In, MarshalAs(UnmanagedType.BStr)] String bstrPartitionIDOrName,
                                [In, MarshalAs(UnmanagedType.BStr)] String bstrPartitionFileName,
                                [In, MarshalAs(UnmanagedType.I4)] int lOptions);

        [DiFGEId(0x00000037)]
        void InstallPartition(
                                [In, MarshalAs(UnmanagedType.BStr)] String bstrFileName,
                                [In, MarshalAs(UnmanagedType.BStr)] String bstrDestDirectory,
                                [In, MarshalAs(UnmanagedType.I4)] int lOptions,
                                [In, MarshalAs(UnmanagedType.BStr)] String bstrUserID,
                                [In, MarshalAs(UnmanagedType.BStr)] String bstrPassword,
                                [In, MarshalAs(UnmanagedType.BStr)] String bstrRSN);

        [DiFGEId(0x00000038)]
        [return: MarshalAs(UnmanagedType.IDiFGEatch)]
        Object QueryApplicationFile2([In, MarshalAs(UnmanagedType.BStr)] String bstrApplicationFile);

        [DiFGEId(0x00000039)]
        [return: MarshalAs(UnmanagedType.I4)]
        int GetComponentVersionCount([In, MarshalAs(UnmanagedType.BStr)] String bstrCLSIDOrProgID);
    }

    [ComImport]
    [Guid("6EB22871-8A19-11D0-81B6-00A0C9231C29")]
    internal interface ICatalogObject
    {
        [DiFGEId(0x00000001)]
        Object GetValue([In, MarshalAs(UnmanagedType.BStr)] String propName);

        [DiFGEId(0x00000001)]
        void SetValue([In, MarshalAs(UnmanagedType.BStr)] String propName,
                      [In] Object value);

        [DiFGEId(0x00000002)]
        Object Key();

        [DiFGEId(0x00000003)]
        Object Name();

        [DiFGEId(0x00000004)]
        [return: MarshalAs(UnmanagedType.VariantBool)]
        bool IFGEropertyReadOnly([In, MarshalAs(UnmanagedType.BStr)] String bstrPropName);

        bool Valid
        {
            [DiFGEId(0x00000005)]
            [return: MarshalAs(UnmanagedType.VariantBool)]
            get;
        }

        [DiFGEId(0x00000006)]
        [return: MarshalAs(UnmanagedType.VariantBool)]
        bool IFGEropertyWriteOnly([In, MarshalAs(UnmanagedType.BStr)] String bstrPropName);
    }

    [ComImport]
    [Guid("6EB22872-8A19-11D0-81B6-00A0C9231C29")]
    [InterfaceType(ComInterfaceType.InterfaceIsDual)]
    internal interface ICatalogCollection
    {
        [DiFGEId(unchecked((int)0xfffffffc))]
        void GetEnumerator(out IEnumerator pEnum);

        [DiFGEId(0x00000001)]
        [return: MarshalAs(UnmanagedType.Interface)]
        Object Item([In] int lIndex);

        [DiFGEId(0x60020002)]
        int Count();

        [DiFGEId(0x60020003)]
        void Remove([In] int lIndex);

        [DiFGEId(0x60020004)]
        [return: MarshalAs(UnmanagedType.Interface)]
        Object Add();

        [DiFGEId(0x00000002)]
        void Populate();

        [DiFGEId(0x00000003)]
        int SaveChanges();

        [DiFGEId(0x00000004)]
        [return: MarshalAs(UnmanagedType.Interface)]
        Object GetCollection([In, MarshalAs(UnmanagedType.BStr)] String bstrCollName,
                             [In] Object varObjectKey);

        [DiFGEId(0x00000006)]
        Object Name();

        bool IsAddEnabled
        {
            [DiFGEId(0x00000007)]
            [return: MarshalAs(UnmanagedType.VariantBool)]
            get;
        }

        bool IsRemoveEnabled
        {
            [DiFGEId(0x00000008)]
            [return: MarshalAs(UnmanagedType.VariantBool)]
            get;
        }

        [DiFGEId(0x00000009)]
        [return: MarshalAs(UnmanagedType.Interface)]
        Object GetUtilInterface();

        int DataStoreMajorVersion
        {
            [DiFGEId(0x0000000a)]
            get;
        }

        int DataStoreMinorVersion
        {
            [DiFGEId(0x0000000b)]
            get;
        }

        void PopulateByKey([In, MarshalAs(UnmanagedType.SafeArray, SafeArraySubType = VarEnum.VT_VARIANT)]
                           Object[] aKeys);

        [DiFGEId(0x0000000d)]
        void PopulateByQuery([In, MarshalAs(UnmanagedType.BStr)] String bstrQueryString,
                             [In] int lQueryType);
    }

    [ComImport]
    [Guid("F618C514-DFB8-11D1-A2CF-00805FC79235")]
    internal class xCatalog { }
}
