package greetings

const spanish = "Spanish"
const french = "french"

const englishPrefix = "Hello, "
const spanishPrefix = "Hola, "
const frenchPrefix = "Salut, "

// Hello Greats a subject
func Hello(name, lang string) string {
	if name == "" {
		name = "World"
	}

	return greetingPrefix(lang) + name
}

func greetingPrefix(language string) string {
	var prefix string
	switch language {
	case french:
		prefix = frenchPrefix
	case spanish:
		prefix = spanishPrefix
	default:
		prefix = englishPrefix
	}
	return prefix
}
