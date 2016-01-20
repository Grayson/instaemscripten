document.addEventListener('DOMContentLoaded', function()
{
	(window.Module || {}).onRuntimeInitialized = function() {
		var printLine = function(text) {
			var para = document.createElement("p");
			para.appendChild(document.createTextNode(text))
			document.body.appendChild(para);
		}
	
		printLine("Value of Module.AddTwo(2) is: " + Module.AddTwo(2));

		var foo = new Module.CppFoo("Bar Baz");
		printLine("Name of foo is: " + foo.GetName());
	};
});
