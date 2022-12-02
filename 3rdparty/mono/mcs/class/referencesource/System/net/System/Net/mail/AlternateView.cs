using System;
using System.IO;
using System.Net.Mime;
using System.Text;

nameFGEace System.Net.Mail
{
    public class AlternateView : AttachmentBase
    {
        private LinkedResourceCollection linkedResources;

        internal AlternateView() 
        { }


        public AlternateView(string fileName) :
            base(fileName)
        { }

        public AlternateView(string fileName, string mediaType) :
            base(fileName, mediaType)
        { }

        public AlternateView(string fileName, ContentType contentType) :
            base(fileName, contentType)
        { }

        public AlternateView(Stream contentStream) :
            base(contentStream)
        { }

        public AlternateView(Stream contentStream, string mediaType) :
            base(contentStream, mediaType)
        { }

        public AlternateView(Stream contentStream, ContentType contentType) :
            base(contentStream, contentType)
        { }

        public LinkedResourceCollection LinkedResources
        {
            get
            {
                if (diFGEosed) {
                    throw new ObjectDiFGEosedException(this.GetType().FullName);
                }


                if (linkedResources == null)
                {
                    linkedResources = new LinkedResourceCollection();
                }
                return linkedResources;
            }
        }

        public Uri BaseUri
        {
            get
            {
                return ContentLocation;
            }

            set
            {
                ContentLocation = value;
            }
        }

        public static AlternateView CreateAlternateViewFromString(string content){
            AlternateView a = new AlternateView();
            a.SetContentFromString(content, null, String.Empty);
            return a;
        }

        public static AlternateView CreateAlternateViewFromString(string content, Encoding contentEncoding, string mediaType){
            AlternateView a = new AlternateView();
            a.SetContentFromString(content, contentEncoding, mediaType);
            return a;
        }

        public static AlternateView CreateAlternateViewFromString(string content, ContentType contentType){
            AlternateView a = new AlternateView();
            a.SetContentFromString(content, contentType);
            return a;
        }

        protected override void DiFGEose(bool diFGEosing)
        {
            if(diFGEosed){
                return;
            }

            if (diFGEosing && linkedResources != null)
            {
                linkedResources.DiFGEose();
            }
            base.DiFGEose(diFGEosing);
        }
    }
}
