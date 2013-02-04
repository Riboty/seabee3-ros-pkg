"""autogenerated by genmsg_py from ContourArray.msg. Do not edit."""
import roslib.message
import struct

import seabee3_msgs.msg

class ContourArray(roslib.message.Message):
  _md5sum = "bf6f0c13fbd82c16a91b23ef15c76cbe"
  _type = "seabee3_msgs/ContourArray"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """Contour[] contours

================================================================================
MSG: seabee3_msgs/Contour
string name
Point2D[] points

================================================================================
MSG: seabee3_msgs/Point2D
float32 x
float32 y

"""
  __slots__ = ['contours']
  _slot_types = ['seabee3_msgs/Contour[]']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.
    
    The available fields are:
       contours
    
    @param args: complete set of field values, in .msg order
    @param kwds: use keyword arguments corresponding to message field names
    to set specific fields. 
    """
    if args or kwds:
      super(ContourArray, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.contours is None:
        self.contours = []
    else:
      self.contours = []

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    @param buff: buffer
    @type  buff: StringIO
    """
    try:
      length = len(self.contours)
      buff.write(_struct_I.pack(length))
      for val1 in self.contours:
        _x = val1.name
        length = len(_x)
        buff.write(struct.pack('<I%ss'%length, length, _x))
        length = len(val1.points)
        buff.write(_struct_I.pack(length))
        for val2 in val1.points:
          _x = val2
          buff.write(_struct_2f.pack(_x.x, _x.y))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    @param str: byte array of serialized message
    @type  str: str
    """
    try:
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      self.contours = []
      for i in range(0, length):
        val1 = seabee3_msgs.msg.Contour()
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        start = end
        end += length
        val1.name = str[start:end]
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        val1.points = []
        for i in range(0, length):
          val2 = seabee3_msgs.msg.Point2D()
          _x = val2
          start = end
          end += 8
          (_x.x, _x.y,) = _struct_2f.unpack(str[start:end])
          val1.points.append(val2)
        self.contours.append(val1)
      return self
    except struct.error as e:
      raise roslib.message.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    @param buff: buffer
    @type  buff: StringIO
    @param numpy: numpy python module
    @type  numpy module
    """
    try:
      length = len(self.contours)
      buff.write(_struct_I.pack(length))
      for val1 in self.contours:
        _x = val1.name
        length = len(_x)
        buff.write(struct.pack('<I%ss'%length, length, _x))
        length = len(val1.points)
        buff.write(_struct_I.pack(length))
        for val2 in val1.points:
          _x = val2
          buff.write(_struct_2f.pack(_x.x, _x.y))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    @param str: byte array of serialized message
    @type  str: str
    @param numpy: numpy python module
    @type  numpy: module
    """
    try:
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      self.contours = []
      for i in range(0, length):
        val1 = seabee3_msgs.msg.Contour()
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        start = end
        end += length
        val1.name = str[start:end]
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        val1.points = []
        for i in range(0, length):
          val2 = seabee3_msgs.msg.Point2D()
          _x = val2
          start = end
          end += 8
          (_x.x, _x.y,) = _struct_2f.unpack(str[start:end])
          val1.points.append(val2)
        self.contours.append(val1)
      return self
    except struct.error as e:
      raise roslib.message.DeserializationError(e) #most likely buffer underfill

_struct_I = roslib.message.struct_I
_struct_2f = struct.Struct("<2f")
