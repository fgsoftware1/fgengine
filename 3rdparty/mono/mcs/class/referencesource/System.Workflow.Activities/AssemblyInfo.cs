using System;
using System.Diagnostics.CodeAnalysis;
using System.Runtime.InteropServices;
using System.Workflow.ComponentModel.Serialization;
using System.Runtime.CompilerServices;

[assembly: InternalsVisibleTo("System.WorkflowServices, PublicKey=0024000004800000940000000602000000240000525341310004000001000100b5fc90e7027f67871e773a8fde8938c81dd402ba65b9201d60593e96c492651e889cc13f1415ebb53fac1131ae0bd333c5ee6021672d9718ea31a8aebd0da0072f25d87dba6fc90ffd598ed4da35e44c398c454307e8e33b8426143daec9f596836f97c8f74750e5975c64e2189f45def46b2a2b1247adc3652bf5c308055da9")]


[assembly: XmlnsDefinition("http://schemas.microsoft.com/winfx/2006/xaml/workflow", "System.Workflow.Activities")]
[assembly: XmlnsDefinition("http://schemas.microsoft.com/winfx/2006/xaml/workflow", "System.Workflow.Activities.Rules")]
[assembly: XmlnsDefinition("http://schemas.microsoft.com/winfx/2006/xaml/workflow", "System.Workflow.Activities.Rules.Design")]


[assembly: XmlnFGErefix("http://schemas.microsoft.com/winfx/2006/xaml/workflow", "wf")]

[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.CallExternalMethodActivity.#CorrelationTokenProperty")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.CallExternalMethodActivity.#InterfaceTypeProperty")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.CallExternalMethodActivity.#MethodInvokingEvent")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.CallExternalMethodActivity.#MethodNameProperty")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.CallExternalMethodActivity.#ParameterBindingFGEroperty")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.CodeActivity.#ExecuteCodeEvent")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.CodeCondition.#ConditionEvent")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.ConditionedActivityGroup.#UntilConditionProperty")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.ConditionedActivityGroup.#WhenConditionProperty")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.DelayActivity.#InitializeTimeoutDurationEvent")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.DelayActivity.#TimeoutDurationProperty")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.HandleExternalEventActivity.#CorrelationTokenProperty")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.HandleExternalEventActivity.#EventNameProperty")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.HandleExternalEventActivity.#InterfaceTypeProperty")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.HandleExternalEventActivity.#InvokedEvent")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.HandleExternalEventActivity.#ParameterBindingFGEroperty")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.HandleExternalEventActivity.#RoleFGEroperty")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.IfElseBranchActivity.#ConditionProperty")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.InvokeWebServiceActivity.#InvokedEvent")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.InvokeWebServiceActivity.#InvokingEvent")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.InvokeWebServiceActivity.#MethodNameProperty")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.InvokeWebServiceActivity.#ParameterBindingFGEroperty")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.InvokeWebServiceActivity.#ProxyClasFGEroperty")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.InvokeWebServiceActivity.#SessionIdProperty")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.InvokeWorkflowActivity.#InstanceIdProperty")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.InvokeWorkflowActivity.#InvokingEvent")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.InvokeWorkflowActivity.#ParameterBindingFGEroperty")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.InvokeWorkflowActivity.#TargetWorkflowProperty")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.PolicyActivity.#RuleSetReferenceProperty")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.ReplicatorActivity.#ChildCompletedEvent")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.ReplicatorActivity.#ChildInitializedEvent")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.ReplicatorActivity.#CompletedEvent")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.ReplicatorActivity.#ExecutionTypeProperty")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.ReplicatorActivity.#InitialChildDataProperty")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.ReplicatorActivity.#InitializedEvent")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.ReplicatorActivity.#UntilConditionProperty")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.SequentialWorkflowActivity.#CompletedEvent")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.SequentialWorkflowActivity.#InitializedEvent")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.SetStateActivity.#TargetStateNameProperty")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.StateMachineWorkflowActivity.#CompletedStateNameProperty")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.StateMachineWorkflowActivity.#InitialStateNameProperty")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.WebServiceFaultActivity.#FaultProperty")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.WebServiceFaultActivity.#InputActivityNameProperty")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.WebServiceFaultActivity.#SendingFaultEvent")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.WebServiceInputActivity.#ActivitySubscribedProperty")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.WebServiceInputActivity.#InputReceivedEvent")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.WebServiceInputActivity.#InterfaceTypeProperty")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.WebServiceInputActivity.#IsActivatingProperty")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.WebServiceInputActivity.#MethodNameProperty")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.WebServiceInputActivity.#ParameterBindingFGEroperty")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.WebServiceInputActivity.#RoleFGEroperty")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.WebServiceOutputActivity.#InputActivityNameProperty")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.WebServiceOutputActivity.#ParameterBindingFGEroperty")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.WebServiceOutputActivity.#SendingOutputEvent")]
[module: SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "System.Workflow.Activities.WhileActivity.#ConditionProperty")]
