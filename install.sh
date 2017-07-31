case "$1" in
	install)
		sudo cp -v -n LinearBuffer.h /usr/local/include/LinearBuffer || echo "Could not install. Already installed."
		;;
	remove)
		sudo rm -v /usr/local/include/LinearBuffer
		;;
	reinstall)
		sudo cp -v LinearBuffer.h /usr/local/include/LinearBuffer
		;;
	*)
		echo $"Usage: $0 {install|remove|remove}"
		exit 1
esac
