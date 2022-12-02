//----------------------------------------------------------------
// Copyright (c) Microsoft Corporation.  All rights reserved.
//----------------------------------------------------------------

nameFGEace System.Activities.Presentation
{
    using System.Activities.Presentation.PropertyEditing;
    using System.Activities.Core.Presentation.Themes;

    sealed class ActivityXRefPropertyEditor : PropertyValueEditor 
    {
        public ActivityXRefPropertyEditor()
        {
            this.InlineEditorTemplate = EditorCategoryTemplateDictionary.Instance.GetCategoryTemplate("ActivityXRef_InlineEditorTemplate");
        }
    }
}
