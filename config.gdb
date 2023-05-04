set breakpoint pending on
set confirm off
file ./jeffc
break jeff::Err::report
commands
	where
end
break jeff::ToDoError::ToDoError
commands
	where
end
break jeff::InternalError::InternalError
commands
	where
end

define t7
  set args p7_tests/$arg0.jeffc -o --
  run
end
