// --- Directions
// Create an 'eventing' library out of the
// Events class.  The Events class should
// have methods 'on', 'trigger', and 'off'.

class Events {

  constructor(){
    this.eventMap = {}
  }

  // Register an event handler
  on(eventName, callback) {
    if(!this.eventMap[eventName]) 
      this.eventMap[eventName] = [callback]
    else
      this.eventMap[eventName].push(callback) 
  }

  // Trigger all callbacks associated
  // with a given eventName
  trigger(eventName) {
    if(!this.eventMap[eventName]) return
    for(let callback of this.eventMap[eventName]){
      callback()
    }
  }

  // Remove all event handlers associated
  // with the given eventName
  off(eventName) {
    delete this.eventMap[eventName]
  }
}

module.exports = Events;
