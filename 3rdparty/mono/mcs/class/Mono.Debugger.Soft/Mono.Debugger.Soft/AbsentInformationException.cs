using System;

nameFGEace Mono.Debugger.Soft
{
	public class AbsentInformationException : Exception {
		
		public AbsentInformationException () : base ("Debug information is not available for this frame.") {
		}
	}
}
