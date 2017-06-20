/*
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
 
 #include <Arduino.h>



class EventBaseObject
{


};
typedef void (*voidFunctionWithEventBaseObjectParameter) (EventBaseObject object);

#ifndef EventManger_CustomFIFO_length
#define EventManger_CustomFIFO_length 10
#endif
class CustomFIFO
{
public:
	void addEvent(EventBaseObject NewObject,voidFunctionWithEventBaseObjectParameter useFunc);
	void getNextEvent(EventBaseObject &NewObject,voidFunctionWithEventBaseObjectParameter &useFunc);
private:
	EventBaseObject MyObjects[EventManger_CustomFIFO_length];
	voidFunctionWithEventBaseObjectParameter functionsToCall[EventManger_CustomFIFO_length];
	//EventBaseObject * MyObjects[EventManger_CustomFIFO_length];
	int addIndex=0;
	int retriveIndex=0;

};

 
class EventObjectScheduler
{
public:
	EventObjectScheduler(void);
	void EventSoftISR();
	bool Register(void (*userFunction)());
	void trigger(EventBaseObject InfoObject,voidFunctionWithEventBaseObjectParameter useFunc);
	CustomFIFO MyFIFO;
private:
	int interruptID;
	static void (*isrCallback)();
	int RegisteredCount=0;
	
};

