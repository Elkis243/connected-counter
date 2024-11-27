from django.shortcuts import get_object_or_404, render
from rest_framework.views import APIView
from rest_framework.response import Response
from .models import Metric
from .serializers import Metric_Serializer

class Metric_counter(APIView): 
    def put(self, request, name):
        try:
            metric = get_object_or_404(Metric, name=name)
            serializer = Metric_Serializer(metric, data=request.data)
            if serializer.is_valid():
                serializer.save()
                return Response({'message': 'Données à jour'})
            else:
                return Response(serializer.errors, status=400)
        except Metric.DoesNotExist:
            return Response({"message": "L'objet n'existe pas"}, status=404)
        
def metrics(request):
    metric = Metric.objects.get(name="counter")
    return render(request, 'counter.html', {
        'metric':metric
    })

def htmx_metrics(request):
    metric = Metric.objects.get(name="counter")
    return render(request, 'metric.html', {
        'metric':metric
    })