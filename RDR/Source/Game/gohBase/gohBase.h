#pragma once



namespace rage
{
	using gohGuid = uint32_t;
	using sagGuid = uint32_t;



	struct Matrix34;



	struct gohBase
	{
		virtual void VFunction000() = 0;
		virtual void VFunction001() = 0;
		virtual void VFunction002() = 0;
		virtual void VFunction003() = 0;
		virtual void VFunction004() = 0;
		virtual void VFunction005() = 0;
		virtual void VFunction006() = 0;
		virtual void VFunction007() = 0;
		virtual void VFunction008() = 0;
		virtual void VFunction009() = 0;
		virtual void VFunction010() = 0;
		virtual void VFunction011() = 0;
		virtual void VFunction012() = 0;
		virtual void VFunction013() = 0;
		virtual void VFunction014() = 0;
		virtual void VFunction015() = 0;
		virtual void VFunction016() = 0;
		virtual void VFunction017() = 0;
		virtual void VFunction018() = 0;
		virtual bool GetPosition(Vector3* _Position) = 0;
		virtual bool GetRotation(Vector3* _Rotation) = 0;
		virtual bool SetPosition(Vector3* _Position, bool _PlaceOnGround) = 0;
		virtual bool SetRotation(Vector3* _Rotation) = 0;

		char m_Padding1[0x024];                      // 0x0008
		e_ObjectType m_ObjectType;                   // 0x002C
		char m_Padding2[0x083];                      // 0x002D
		sagGuid m_Guid;                              // 0x00B0
	};
}