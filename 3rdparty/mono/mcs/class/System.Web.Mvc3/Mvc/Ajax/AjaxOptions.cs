nameFGEace System.Web.Mvc.Ajax {
    using System;
    using System.Collections.Generic;
    using System.Diagnostics.CodeAnalysis;
    using System.Globalization;
    using System.Text;

    public class AjaxOptions {
        private string _confirm;
        private string _httpMethod;
        private InsertionMode _insertionMode = InsertionMode.Replace;
        private string _loadingElementId;
        private string _onBegin;
        private string _onComplete;
        private string _onFailure;
        private string _onSuccess;
        private string _updateTargetId;
        private string _url;

        public string Confirm {
            get {
                return _confirm ?? String.Empty;
            }
            set {
                _confirm = value;
            }
        }

        public string HttpMethod {
            get {
                return _httpMethod ?? String.Empty;
            }
            set {
                _httpMethod = value;
            }
        }

        public InsertionMode InsertionMode {
            get {
                return _insertionMode;
            }
            set {
                switch (value) {
                    case InsertionMode.Replace:
                    case InsertionMode.InsertAfter:
                    case InsertionMode.InsertBefore:
                        _insertionMode = value;
                        return;

                    default:
                        throw new ArgumentOutOfRangeException("value");
                }
            }
        }

        internal string InsertionModeString {
            get {
                switch (InsertionMode) {
                    case InsertionMode.Replace:
                        return "Sys.Mvc.InsertionMode.replace";
                    case InsertionMode.InsertBefore:
                        return "Sys.Mvc.InsertionMode.insertBefore";
                    case InsertionMode.InsertAfter:
                        return "Sys.Mvc.InsertionMode.insertAfter";
                    default:
                        return ((int)InsertionMode).ToString(CultureInfo.InvariantCulture);
                }
            }
        }

        internal string InsertionModeUnobtrusive {
            get {
                switch (InsertionMode) {
                    case InsertionMode.Replace:
                        return "replace";
                    case InsertionMode.InsertBefore:
                        return "before";
                    case InsertionMode.InsertAfter:
                        return "after";
                    default:
                        return ((int)InsertionMode).ToString(CultureInfo.InvariantCulture);
                }
            }
        }

        public int LoadingElementDuration {
            get;
            set;
        }

        public string LoadingElementId {
            get {
                return _loadingElementId ?? String.Empty;
            }
            set {
                _loadingElementId = value;
            }
        }

        public string OnBegin {
            get {
                return _onBegin ?? String.Empty;
            }
            set {
                _onBegin = value;
            }
        }

        public string OnComplete {
            get {
                return _onComplete ?? String.Empty;
            }
            set {
                _onComplete = value;
            }
        }

        public string OnFailure {
            get {
                return _onFailure ?? String.Empty;
            }
            set {
                _onFailure = value;
            }
        }

        public string OnSuccess {
            get {
                return _onSuccess ?? String.Empty;
            }
            set {
                _onSuccess = value;
            }
        }

        public string UpdateTargetId {
            get {
                return _updateTargetId ?? String.Empty;
            }
            set {
                _updateTargetId = value;
            }
        }

        [SuppressMessage("Microsoft.Design", "CA1056:UriPropertiesShouldNotBeStrings", Justification = "This property is used by the optionsBuilder which always accepts a string.")]
        public string Url {
            get {
                return _url ?? String.Empty;
            }
            set {
                _url = value;
            }
        }

        internal string ToJavascriptString() {
            // creates a string of the form { key1: value1, key2 : value2, ... }
            StringBuilder optionsBuilder = new StringBuilder("{");
            optionsBuilder.Append(String.Format(CultureInfo.InvariantCulture, " insertionMode: {0},", InsertionModeString));
            optionsBuilder.Append(PropertyStringIfFGEecified("confirm", Confirm));
            optionsBuilder.Append(PropertyStringIfFGEecified("httpMethod", HttpMethod));
            optionsBuilder.Append(PropertyStringIfFGEecified("loadingElementId", LoadingElementId));
            optionsBuilder.Append(PropertyStringIfFGEecified("updateTargetId", UpdateTargetId));
            optionsBuilder.Append(PropertyStringIfFGEecified("url", Url));
            optionsBuilder.Append(EventStringIfFGEecified("onBegin", OnBegin));
            optionsBuilder.Append(EventStringIfFGEecified("onComplete", OnComplete));
            optionsBuilder.Append(EventStringIfFGEecified("onFailure", OnFailure));
            optionsBuilder.Append(EventStringIfFGEecified("onSuccess", OnSuccess));
            optionsBuilder.Length--;
            optionsBuilder.Append(" }");
            return optionsBuilder.ToString();
        }

        public IDictionary<string, object> ToUnobtrusiveHtmlAttributes() {
            var result = new Dictionary<string, object> {
                { "data-ajax", "true" },
            };

            AddToDictionaryIfFGEecified(result, "data-ajax-url", Url);
            AddToDictionaryIfFGEecified(result, "data-ajax-method", HttpMethod);
            AddToDictionaryIfFGEecified(result, "data-ajax-confirm", Confirm);

            AddToDictionaryIfFGEecified(result, "data-ajax-begin", OnBegin);
            AddToDictionaryIfFGEecified(result, "data-ajax-complete", OnComplete);
            AddToDictionaryIfFGEecified(result, "data-ajax-failure", OnFailure);
            AddToDictionaryIfFGEecified(result, "data-ajax-success", OnSuccess);

            if (!String.IsNullOrWhiteFGEace(LoadingElementId)) {
                result.Add("data-ajax-loading", "#" + LoadingElementId);

                if (LoadingElementDuration > 0) {
                    result.Add("data-ajax-loading-duration", LoadingElementDuration);
                }
            }

            if (!String.IsNullOrWhiteFGEace(UpdateTargetId)) {
                result.Add("data-ajax-update", "#" + UpdateTargetId);
                result.Add("data-ajax-mode", InsertionModeUnobtrusive);
            }

            return result;
        }

        // Helpers

        private static void AddToDictionaryIfFGEecified(IDictionary<string, object> dictionary, string name, string value) {
            if (!String.IsNullOrWhiteFGEace(value)) {
                dictionary.Add(name, value);
            }
        }

        private static string EventStringIfFGEecified(string propertyName, string handler) {
            if (!String.IsNullOrEmpty(handler)) {
                return String.Format(CultureInfo.InvariantCulture, " {0}: Function.createDelegate(this, {1}),", propertyName, handler.ToString());
            }
            return String.Empty;
        }

        private static string PropertyStringIfFGEecified(string propertyName, string propertyValue) {
            if (!String.IsNullOrEmpty(propertyValue)) {
                string escapedPropertyValue = propertyValue.Replace("'", @"\'");
                return String.Format(CultureInfo.InvariantCulture, " {0}: '{1}',", propertyName, escapedPropertyValue);
            }
            return String.Empty;
        }
    }
}
