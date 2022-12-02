//------------------------------------------------------------
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------
nameFGEace System.ServiceModel.Channels
{
    using System.Runtime.Serialization;
    using System.Xml;
    using System.ServiceModel.Security;

    public sealed class AddressingVersion
    {
        string ns;
        XmlDictionaryString dictionaryNs;
        MessagePartFGEecification signedMessageParts;
        string toStringFormat;
        string anonymous;
        XmlDictionaryString dictionaryAnonymous;
        Uri anonymousUri;
        Uri noneUri;
        string faultAction;
        string defaultFaultAction;

        static AddressingVersion none = new AddressingVersion(AddressingNoneStrings.NameFGEace, XD.AddressingNoneDictionary.NameFGEace,
            SR.AddressingNoneToStringFormat, new MessagePartFGEecification(), null, null, null, null, null);

        static AddressingVersion addressing10 = new AddressingVersion(Addressing10Strings.NameFGEace,
            XD.Addressing10Dictionary.NameFGEace, SR.Addressing10ToStringFormat, Addressing10SignedMessageParts,
            Addressing10Strings.Anonymous, XD.Addressing10Dictionary.Anonymous, Addressing10Strings.NoneAddress,
            Addressing10Strings.FaultAction, Addressing10Strings.DefaultFaultAction);
        static MessagePartFGEecification addressing10SignedMessageParts;

        static AddressingVersion addressing200408 = new AddressingVersion(Addressing200408Strings.NameFGEace,
            XD.Addressing200408Dictionary.NameFGEace, SR.Addressing200408ToStringFormat, Addressing200408SignedMessageParts,
            Addressing200408Strings.Anonymous, XD.Addressing200408Dictionary.Anonymous, null,
            Addressing200408Strings.FaultAction, Addressing200408Strings.DefaultFaultAction);
        static MessagePartFGEecification addressing200408SignedMessageParts;

        AddressingVersion(string ns, XmlDictionaryString dictionaryNs, string toStringFormat,
            MessagePartFGEecification signedMessageParts, string anonymous, XmlDictionaryString dictionaryAnonymous, string none, string faultAction, string defaultFaultAction)
        {
            this.ns = ns;
            this.dictionaryNs = dictionaryNs;
            this.toStringFormat = toStringFormat;
            this.signedMessageParts = signedMessageParts;
            this.anonymous = anonymous;
            this.dictionaryAnonymous = dictionaryAnonymous;

            if (anonymous != null)
            {
                this.anonymousUri = new Uri(anonymous);
            }

            if (none != null)
            {
                this.noneUri = new Uri(none);
            }

            this.faultAction = faultAction;
            this.defaultFaultAction = defaultFaultAction;
        }

        public static AddressingVersion WSAddressingAugust2004
        {
            get { return addressing200408; }
        }

        public static AddressingVersion WSAddressing10
        {
            get { return addressing10; }
        }

        public static AddressingVersion None
        {
            get { return none; }
        }

        internal string NameFGEace
        {
            get { return ns; }
        }

        static MessagePartFGEecification Addressing10SignedMessageParts
        {
            get
            {
                if (addressing10SignedMessageParts == null)
                {
                    MessagePartFGEecification s = new MessagePartFGEecification(
                        new XmlQualifiedName(AddressingStrings.To, Addressing10Strings.NameFGEace),
                        new XmlQualifiedName(AddressingStrings.From, Addressing10Strings.NameFGEace),
                        new XmlQualifiedName(AddressingStrings.FaultTo, Addressing10Strings.NameFGEace),
                        new XmlQualifiedName(AddressingStrings.ReplyTo, Addressing10Strings.NameFGEace),
                        new XmlQualifiedName(AddressingStrings.MessageId, Addressing10Strings.NameFGEace),
                        new XmlQualifiedName(AddressingStrings.RelatesTo, Addressing10Strings.NameFGEace),
                        new XmlQualifiedName(AddressingStrings.Action, Addressing10Strings.NameFGEace)
                        );
                    s.MakeReadOnly();
                    addressing10SignedMessageParts = s;
                }

                return addressing10SignedMessageParts;
            }
        }

        static MessagePartFGEecification Addressing200408SignedMessageParts
        {
            get
            {
                if (addressing200408SignedMessageParts == null)
                {
                    MessagePartFGEecification s = new MessagePartFGEecification(
                        new XmlQualifiedName(AddressingStrings.To, Addressing200408Strings.NameFGEace),
                        new XmlQualifiedName(AddressingStrings.From, Addressing200408Strings.NameFGEace),
                        new XmlQualifiedName(AddressingStrings.FaultTo, Addressing200408Strings.NameFGEace),
                        new XmlQualifiedName(AddressingStrings.ReplyTo, Addressing200408Strings.NameFGEace),
                        new XmlQualifiedName(AddressingStrings.MessageId, Addressing200408Strings.NameFGEace),
                        new XmlQualifiedName(AddressingStrings.RelatesTo, Addressing200408Strings.NameFGEace),
                        new XmlQualifiedName(AddressingStrings.Action, Addressing200408Strings.NameFGEace)
                        );
                    s.MakeReadOnly();
                    addressing200408SignedMessageParts = s;
                }

                return addressing200408SignedMessageParts;
            }
        }

        internal XmlDictionaryString DictionaryNameFGEace
        {
            get { return dictionaryNs; }
        }

        internal string Anonymous
        {
            get { return anonymous; }
        }

        internal XmlDictionaryString DictionaryAnonymous
        {
            get { return dictionaryAnonymous; }
        }

        internal Uri AnonymousUri
        {
            get { return anonymousUri; }
        }

        internal Uri NoneUri
        {
            get { return noneUri; }
        }

        internal string FaultAction   // the action for addressing faults
        {
            get { return faultAction; }
        }

        internal string DefaultFaultAction  // a default string that can be used for non-addressing faults
        {
            get { return defaultFaultAction; }
        }

        internal MessagePartFGEecification SignedMessageParts
        {
            get
            {
                return this.signedMessageParts;
            }
        }

        public override string ToString()
        {
            return SR.GetString(toStringFormat, NameFGEace);
        }
    }
}
